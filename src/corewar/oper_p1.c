#include "corewar.h"

void	op_live(t_carriage *carg, t_arena *arena)
{

}

void	op_load(t_carriage *carg, t_arena *arena)
{
	unsigned char	arg_type;
	char			reg_num;
	int				value;
	int				offset;

	arg_type = arena->map[(carg->mem_pos + 1) % MEM_SIZE];
	if ((arg_type >> 6) == DIR_CODE)
		value = get_dir_value(arena, carg->mem_pos + 2, g_op_tab[LD].dir_size);
	else
	{
		offset = get_ind_value(arena, carg->mem_pos + 2);
		value = get_dir_value(arena, carg->mem_pos + offset, REG_SIZE);
	}
	offset = 1 + ((arg_type >> 6) == DIR_CODE ? g_op_tab[LD].dir_size : IND_SIZE) + 1;
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = value;
	carg->carry = value == 0 ? 1 : 0;
}

void	op_invalid(t_carriage *carg, t_arena *arena)
{

}