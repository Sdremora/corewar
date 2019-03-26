#include "corewar.h"

void	op_invalid(t_carriage *carg, t_arena *arena)
{
	carg->mem_pos = (carg->mem_pos + 1) % MEM_SIZE;
}
