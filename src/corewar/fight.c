#include "corewar.h"


int			check_arg_bites(int op_id, int arg)
{
	if (arg == 1)
	{
		if (op_id & 1)
			return (1);
	}
	if (arg == 2)
	{
		if ((op_id >> 1) & 1)
			return (1);
	}
	if (arg == 3)
	{
		if (op_id > 3)
			return (1);
	}
	if (!arg && !op_id)
		return (1);
	return (0);
}

int			step_bites(int arg, int dir_size) //счетчик отступов для аргументов
{
	if (arg == T_REG)
		return (1);
	if (arg == T_DIR)
		return (dir_size);
	if (arg == T_IND)
		return (2);
	if (arg == 0)
		return (0);
	return (-42);
}

int			step_args(int t_dir_size_eq_2, unsigned char arg)
{
	int res;

	res = 0;
	res += step_bites(t_dir_size_eq_2, arg >> 6);
	res += step_bites(t_dir_size_eq_2, arg >> 4 & 3);
	res += step_bites(t_dir_size_eq_2, arg >> 2 & 3);
	return (res);
}
/*
int			check_code_args(t_carriage *carg, t_arena *arena)
{
	unsigned char	oper;
	unsigned char	arg;
	int				res;

	res = 1;
	oper = arena->map[carg->mem_pos] - 1;
	arg = arena->map[(carg->mem_pos + 1) % MEM_SIZE];
	carg->args[0] = arg >> 6;
	carg->args[1] = arg >> 4 & 3;
	carg->args[2] = arg >> 2 & 3;
	res *= check_arg_bites(g_op_tab[oper].args[0], carg->args[0]);
	res *= check_arg_bites(g_op_tab[oper].args[1], carg->args[1]);
	res *= check_arg_bites(g_op_tab[oper].args[2], carg->args[2]);
	return (res);
}
*/

static void	operations_sort(t_carriage *carg, t_arena *arena)
{
	unsigned char	oper;

	oper = arena->map[carg->mem_pos] - 1;
	if (oper >= LIVE && oper <= AFF)
	{
//		if (check_code_args(oper, arena->map[(carg->mem_pos + 1) % MEM_SIZE]))
//		{
			carg->pause_count = g_op_tab[oper].cost;
			carg->op_id = oper;
//		}
//		else
//		{
//			carg->mem_pos = (carg->mem_pos + 2 + step_args(g_op_tab[oper].dir_size, arena->map[(carg->mem_pos + 1) % MEM_SIZE])) % MEM_SIZE;
//		}
//		move_carriage(carg, arena);
	}
	else
		op_invalid(carg, arena);
}

int			convert_args(unsigned char arg)
{
	if (arg == REG_CODE)
		return (T_REG);
	if (arg == DIR_CODE)
		return (T_DIR);
	if (arg == IND_CODE)
		return (T_IND);
	return (0);	
}

void		load_args(t_carriage *carg, t_arena *arena)
{
	unsigned char	arg;
	unsigned char	temp;

	arg = arena->map[(carg->mem_pos + 1) % MEM_SIZE];
	carg->args[0] = convert_args(arg >> 6);
	carg->args[1] = convert_args(arg >> 4 & 3);
	carg->args[2] = convert_args(arg >> 2 & 3);
	carg->args[3] = convert_args(arg & 3);
	
}

int			check_code_args(int args[4], unsigned char op_id)
{
	int	res;
	int i;


	res = 1;
	i = 0;
	while (i < 5)
	{
		if (g_op_tab[op_id].args[i] && args[i])
			res *= ((args[i] & g_op_tab[op_id].args[i]) > 0);
		else if (g_op_tab[op_id].args[i] != args[i])
			return (0);
		i++;
	}
	return (res);
}

void		move_carriage(t_carriage *carg, int dir_size)
{
	int move;
	int args[4];

	move = 2;
	move += step_bites(carg->args[0], dir_size) + step_bites(carg->args[1], dir_size)
			+ step_bites(carg->args[2], dir_size) + step_bites(carg->args[3], dir_size);
	carg->mem_pos = (carg->mem_pos + move) % MEM_SIZE;
	

}

static void	play_round(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;

    carg_node = arena->carg_lst;
    while (carg_node)
    {
		carg = (t_carriage *)carg_node->content;
        if (carg->pause_count > 0)
			carg->pause_count--;
		else if (carg->op_id > -1)
		{
			load_args(carg, arena);
			if (check_code_args(carg->args, arena->map[carg->mem_pos] - 1))
				g_op_tab[carg->op_id].op_handler(carg, arena);
			move_carriage(carg, g_op_tab[arena->map[carg->mem_pos] - 1].dir_size);
		}
		else
			operations_sort(carg, arena);
    	carg_node = carg_node->next;
    }
}

void		fight(t_arena *arena)
{
    int			carg_count;
	int			i;

	i = 0;
    while (arena->carg_lst)
    {
		arena->cur_cycle++;
		play_round(arena);
		i++;
		if (i > 50)
			break;
    }
    arena_print(arena);
}
