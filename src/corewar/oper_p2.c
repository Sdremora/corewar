#include "corewar.h"

/*
**	jump if non-zero
**	T_DIR
*/

void	op_zjmp(t_carriage *carg, t_arena *arena)
{
	int	offset;

	offset = get_args_offset(carg, 0);
	if (carg->carry)
		offset = get_value(arena, carg, offset, carg->args[0]) % IDX_MOD;
	else
		offset = get_args_offset(carg, 1);
	carg->mem_pos = (carg->mem_pos + offset) % MEM_SIZE;
}

/*
**	load index
**	T_REG / T_DIR / T_IND : T_REG / T_DIR : T_REG
*/

void	op_ldi(t_carriage *carg, t_arena *arena)
{

}

/*
**	store index
**	T_REG : T_REG / T_DIR / T_IND : T_REG / T_DIR
*/

void	op_sti(t_carriage *carg, t_arena *arena)
{

}

/*
**	fork
**	T_DIR
*/

void	op_fork(t_carriage *carg, t_arena *arena)
{

}

/*
**	write on console
**	T_REG
*/

void	op_aff(t_carriage *carg, t_arena *arena)
{

}

void	op_invalid(t_carriage *carg, t_arena *arena)
{
	carg->mem_pos = (carg->mem_pos + 1) % MEM_SIZE;
}
