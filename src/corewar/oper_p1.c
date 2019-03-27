#include "corewar.h"

/*
**	live
**	T_DIR
*/

void	op_live(t_carriage *carg, t_arena *arena)
{
	int	player_num;

	carg->last_live_cycle = arena->cur_cycle;
	carg->live = 1;
	player_num = read_arg(arena, carg, 0, TRUE) * -1;
	if (player_num >= 1 && player_num <= arena->players_count)
		arena->last_live_player = player_num - 1;
	arena->live_call_count++;
}

/*
**	load
**	T_DIR / T_IND : T_REG
*/

void	op_ld_lld(t_carriage *carg, t_arena *arena)
{
	char			is_idx_mod;
	int				value;
	int				offset;

	is_idx_mod = carg->op_id == LD ? TRUE : FALSE;
	value = read_arg(arena, carg, 0, is_idx_mod);
	offset = get_args_offset(carg, 1);
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = value;
	carg->carry = value == 0 ? 1 : 0;
}

/*
**	store
**	T_REG : T_REG / T_IND
*/

void	op_st(t_carriage *carg, t_arena *arena)
{
	int	value;
	int	offset;

	offset = get_args_offset(carg, 0);
	value = carg->reg[get_reg_num(arena, carg->mem_pos + offset)];
	offset = get_args_offset(carg, 1);
	if (carg->args[1] == T_REG)
		carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = value;
	else
	{
		offset = get_value(arena, carg->mem_pos + offset, IND_SIZE) % IDX_MOD;
		put_value(arena, carg->mem_pos + offset, value);
	}
}

/*
**	addition or soustraction
**	T_REG	T_REG	T_REG
*/

void	op_add_sub(t_carriage *carg, t_arena *arena)
{
	int	n1;
	int	n2;
	int	n3;

	n1 = carg->reg[get_reg_num(arena, carg->mem_pos + 2)];
	n2 = carg->reg[get_reg_num(arena, carg->mem_pos + 3)];
	if (carg->op_id == ADD)
		n3 = n1 + n2;
	else
		n3 = n1 - n2;
	carg->reg[get_reg_num(arena, carg->mem_pos + 4)] = n3;
	carg->carry = n3 == 0 ? 1 : 0;
}

/*
**	bitwise AND (&) : bitwise OR (|) : bitwise XOR (^)
**	T_REG / T_DIR / T_IND : T_REG / T_DIR / T_IND : T_REG
*/

void	op_and_or_xor(t_carriage *carg, t_arena *arena)
{
	int	n1;
	int	n2;
	int	n3;
	int	offset;

	n1 = read_arg(arena, carg, 0, TRUE);
	n2 = read_arg(arena, carg, 1, TRUE);
	if (carg->op_id == AND)
		n3 = n1 & n2;
	else if (carg->op_id == OR)
		n3 = n1 | n2;
	else
		n3 = n1 ^ n2;
	offset = get_args_offset(carg, 2);
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = n3;
	carg->carry = n3 == 0 ? 1 : 0;
}
