#include "corewar.h"

void	op_live(t_carriage *carg, t_arena *arena)
{
	int	player_num;

	carg->last_live = arena->cur_cycle;
	player_num = get_value(arena, carg->mem_pos + 1, 1) * -1;
	if (player_num >= 1 && player_num <= arena->players_count)
		arena->last_live_player = player_num;
	arena->live_call_count++;
}

void	op_load(t_carriage *carg, t_arena *arena)
{
	unsigned char	arg_type;
	char			reg_num;
	int				value;
	int				offset;

	arg_type = arena->map[(carg->mem_pos + 1) % MEM_SIZE];
	if (carg->args[0] == T_DIR)
		value = get_value(arena, carg->mem_pos + 2, g_op_tab[LD].dir_size);
	else
	{
		offset = get_value(arena, carg->mem_pos + 2, IND_SIZE) % IDX_MOD;
		value = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	}
	offset = 1 + (carg->args[0] == T_DIR ? g_op_tab[LD].dir_size : IND_SIZE) + 1;
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = value;
	carg->carry = value == 0 ? 1 : 0;
}

void	op_store(t_carriage *carg, t_arena *arena)
{
	int	value;
	int	offset;

	value = carg->reg[get_reg_num(arena, carg->mem_pos + 2)];
	if (carg->args[1] == T_REG)
		carg->reg[get_reg_num(arena, carg->mem_pos + 3)] = value;
	else
	{
		offset = get_value(arena, carg->mem_pos + 3, IND_SIZE) % IDX_MOD;
		put_value(arena, carg->mem_pos + offset, value);
	}
}

void	op_invalid(t_carriage *carg, t_arena *arena)
{
	carg->mem_pos = (carg->mem_pos + 1) % MEM_SIZE;
}