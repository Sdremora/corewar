#include "corewar.h"

/*
**	jump if non-zero
**	T_DIR
*/

void	op_zjmp(t_carriage *carg, t_arena *arena)
{
	int		offset;
	int		value;
	char	*answer;

	value = read_arg(arena, carg, ARG_1, TRUE);
	if (carg->carry)
	{
		offset =  value % IDX_MOD;
		carg->mem_pos = get_pos(carg->mem_pos + offset);
		answer = "OK";
	}
	else
		answer = "FAILED";
	if (arena->flags[F_V] & 4)
		ft_printf("P %4d | %s %d %s\n", carg->carg_id, g_op_tab[ZJMP].name,
		value, answer);
}

/*
**	load index and long load index
**	T_REG / T_DIR / T_IND : T_REG / T_DIR : T_REG
*/

void	op_ldi_lldi(t_carriage *carg, t_arena *arena)
{
	int n1;
	int n2;
	int	reg_num;
	int n3;
	int offset;

	n1 = read_arg(arena, carg, ARG_1, TRUE);
	n2 = read_arg(arena, carg, ARG_2, TRUE);
	offset = n1 + n2;
	offset = carg->op_id == LDI ? offset % IDX_MOD : offset;
	n3 = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	reg_num = get_reg_num(arena, carg->mem_pos + get_args_offset(carg, ARG_3));
	carg->reg[reg_num] = n3;
	if (arena->flags[F_V] & 4)
	{
		ft_printf("P %4d | %s %d %d r%d\n", carg->carg_id, g_op_tab[carg->op_id].name,
			n1, n2, reg_num + 1);
		ft_printf("%7.s| -> load from %d + %d = %d (with pc and mod %d)\n",
			"", n1, n2, n1 + n2, offset + carg->mem_pos);
	}
}

/*
**	store index
**	T_REG : T_REG / T_DIR / T_IND : T_REG / T_DIR
*/

void	op_sti(t_carriage *carg, t_arena *arena)
{
	int offset;
	int n2;
	int n3;
	int value;
	int	reg_num;

	reg_num = get_reg_num(arena, carg->mem_pos + get_args_offset(carg, ARG_1));
	value = carg->reg[reg_num];
	n2 = read_arg(arena, carg, ARG_2, TRUE);
	n3 = read_arg(arena, carg, ARG_3, TRUE);
	offset = (n2 + n3) % IDX_MOD;
	put_value(arena, carg->mem_pos + offset, value, carg->owner);
	if (arena->flags[F_V] & 4)
	{
		ft_printf("P %4d | %s r%d %d %d\n", carg->carg_id, g_op_tab[carg->op_id].name,
			reg_num + 1, n2, n3);
		ft_printf("%7.s| -> store to %d + %d = %d (with pc and mod %d)\n",
			"", n2, n3, n2 + n3, offset + carg->mem_pos);
	}
}

/*
**	fork
**	T_DIR
*/

void	op_fork(t_carriage *carg, t_arena *arena)
{
	int			n1;
	int			offset;
	t_list		*node;
	t_carriage	*new_carg;

	node = NULL;
	arena->max_carg_id++;
	new_carg = carriage_copy(carg, arena->max_carg_id);
	node = ft_lstput(new_carg, sizeof(t_carriage));
	if (new_carg == NULL || node == NULL)
	{
		carriage_free(&new_carg);
		free(node);
		error_handle(E_NO_MEM, arena, NULL);
	}
	ft_lstadd(&arena->carg_lst, node);
	n1 = read_arg(arena, carg, ARG_1, TRUE);
	offset = carg->op_id == FORK ? n1 % IDX_MOD : n1;
	new_carg->mem_pos = get_pos(carg->mem_pos + offset);
	if (arena->flags[F_V] & 4)
		ft_printf("P %4d | %s %d (%d)\n", carg->carg_id, g_op_tab[carg->op_id].name,
		n1, carg->mem_pos + offset);
}

/*
**	write on console
**	T_REG
*/

void	op_aff(t_carriage *carg, t_arena *arena)
{

}

