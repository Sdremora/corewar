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

int			step_bites(int t_dir_size_eq_2, unsigned char arg) //счетчик отступов для аргументов
{
	if (arg == 1)
		return (1);
	if (arg == 2)
		if (t_dir_size_eq_2)
			return (2);
		return (4);
	if (arg == 3)
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

int			check_code_args(t_oper oper_id, unsigned char arg_type) //unsigned char, т.к. char(=t_arg_type) vse lomaet
{
	int res;
	int temp;

	res = 1;
	res *= check_arg_bites(g_op_tab[oper_id].args[0], arg_type >> 6);
	res *= check_arg_bites(g_op_tab[oper_id].args[1], arg_type >> 4 & 3);
	res *= check_arg_bites(g_op_tab[oper_id].args[2], arg_type >> 2 & 3);
	return (res);
}

void		move_carriage(t_carriage *carg, t_arena *arena)
{

}

static void	operations_sort(t_carriage *carg, t_arena *arena)
{
	unsigned char	instruct;

	instruct = arena->map[carg->mem_pos] - 1;// сдвинул instruct и live чтобы все время не писать -1
	if (instruct >= LIVE && instruct <= AFF)
	{
		if (check_code_args(instruct, arena->map[(carg->mem_pos + 1) % MEM_SIZE]))
		{
			carg->pause_count = g_op_tab[instruct].cost;
			carg->op_id = instruct;
//			g_op_tab[instruct].op_handler(carg, arena);  перенес в play_round
		}
		else
		{
			carg->mem_pos = (carg->mem_pos + 2 + step_args(g_op_tab[instruct].t_dir_size_eq_2, arena->map[(carg->mem_pos + 1) % MEM_SIZE])) % MEM_SIZE;
		}
//		move_carriage(carg, arena);
	}
	else
		op_invalid(carg, arena);
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
			g_op_tab[carg->op_id].op_handler(carg, arena);
		else
		{	
			operations_sort(carg, arena);
			carg->op_id = -1;
		}
    	carg_node = carg_node->next;
    }
}

void		fight(t_arena *arena)
{
    int			carg_count;

    while (arena->carg_lst)
    {
			arena->cur_cycle++;
			play_round(arena);
			break;
    }
    arena_print(arena);
}
