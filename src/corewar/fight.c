#include "corewar.h"

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

static void	operations_sort(t_carriage *carg, t_arena *arena)
{
	unsigned char	oper;

	oper = arena->map[carg->mem_pos] - 1;
	if (oper >= LIVE && oper <= AFF)
	{
			carg->pause_count = g_op_tab[oper].cost;
			carg->op_id = oper;
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

	if (g_op_tab[carg->op_id].kod_tipov_argumenta)
	{
		arg = arena->map[(carg->mem_pos + 1) % MEM_SIZE];
		carg->args[0] = convert_args(arg >> 6);
		carg->args[1] = convert_args(arg >> 4 & 3);
		carg->args[2] = convert_args(arg >> 2 & 3);
		carg->args[3] = convert_args(arg & 3);
	}
	else
		carg->args[0] = T_DIR;
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

	move = 1 + g_op_tab[carg->op_id].kod_tipov_argumenta;
	move += step_bites(carg->args[0], dir_size) + step_bites(carg->args[1], dir_size)
			+ step_bites(carg->args[2], dir_size) + step_bites(carg->args[3], dir_size);
	carg->mem_pos = (carg->mem_pos + move) % MEM_SIZE;
}
void		clean_carg_op(t_carriage *carg)
{
	carg->op_id = -1;
	ft_bzero(carg->args, sizeof(int) * 4);
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
			if (!g_op_tab[carg->op_id].kod_tipov_argumenta
			|| check_code_args(carg->args, arena->map[carg->mem_pos] - 1))
				g_op_tab[carg->op_id].op_handler(carg, arena);
			move_carriage(carg, g_op_tab[arena->map[carg->mem_pos] - 1].dir_size);
			clean_carg_op(carg);
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
