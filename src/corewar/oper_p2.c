#include "corewar.h"

/*
**	jump if non-zero
**	T_DIR
*/

void	op_zjmp(t_carriage *carg, t_arena *arena)
{
	int		offset;
	char	*answer;

	offset = get_args_offset(carg, 0);
	if (carg->carry)
	{
		offset = read_arg(arena, carg, 0, TRUE) % IDX_MOD;
		answer = "OK";
	}
	else
	{
		offset += get_arg_len(ZJMP, T_DIR);
		answer = "KO";
	}
	carg->mem_pos = (carg->mem_pos + offset) % MEM_SIZE;
	ft_printf("P %4d | %s %d %s\n", carg->owner, g_op_tab[ZJMP].name,
		offset, answer);
}

/*
**	load index and long load index
**	T_REG / T_DIR / T_IND : T_REG / T_DIR : T_REG
*/

void	op_ldi_lldi(t_carriage *carg, t_arena *arena)
{
	int n1;
	int n2;
	int n3;
	int offset;

	n1 = read_arg(arena, carg, 0, TRUE);
	n2 = read_arg(arena, carg, 1, TRUE);
	offset = n1 + n2;
	offset = carg->op_id == LDI ? offset % IDX_MOD : offset;
	n3 = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	offset = get_args_offset(carg, 2);
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = n3;
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

	n2 = read_arg(arena, carg, 1, TRUE);
	n3 = read_arg(arena, carg, 2, TRUE);
	offset = (n2 + n3) % IDX_MOD;
	value = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	offset = get_args_offset(carg, 0);
	carg->reg[get_reg_num(arena, carg->mem_pos + offset)] = value;
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
	new_carg = carriage_copy(carg);
	node = ft_lstput(new_carg, sizeof(t_carriage));
	if (new_carg == NULL || node == NULL)
	{
		carriage_free(&new_carg);
		free(node);
		error_handle(E_NO_MEM, arena, NULL);
	}
	ft_lstadd(&arena->carg_lst, node);
	n1 = read_arg(arena, carg, 0, TRUE);
	offset = carg->op_id == FORK ? n1 % IDX_MOD : n1;
	new_carg->mem_pos = (carg->mem_pos + offset) % MEM_SIZE;
	ft_printf("P %4d | %s %d (%d)\n", carg->owner, g_op_tab[carg->op_id].name,
		n1, carg->mem_pos + offset);
}

/*
**	write on console
**	T_REG
*/

void	op_aff(t_carriage *carg, t_arena *arena)
{

}

