#include "corewar.h"


int			check_code_args(t_oper oper_id, t_arg_type arg_type)
{

	return (1);
}

void		move_carriage(t_carriage *carg, t_arena *arena)
{

}

static void	operations_sort(t_carriage *carg, t_arena *arena)
{
	unsigned char	instruct;

	instruct = arena->map[carg->mem_pos];
	if (instruct >= LIVE && instruct <= AFF)
	{
		if (check_code_args(LIVE, arena->map[(carg->mem_pos + 1) % MEM_SIZE]))
			g_op_tab[instruct - 1].op_handler(carg, arena);
		move_carriage(carg, arena);
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
		else
			operations_sort(carg, arena);
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
