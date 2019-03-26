#include "corewar.h"

int		get_value(t_arena *arena, t_carriage *carg, int mem_offset, char arg_type)
{
	int			i;
	int			len;
	t_converter converter;

	if (arg_type == T_REG)
		len = REG_SIZE;
	else if (arg_type == T_IND)
		len = IND_SIZE;
	else
		len = g_op_tab[carg->op_id].dir_size;
	converter.n = 0;
	i = 0;
	while (i < len)
	{
		converter.str[i] = arena->map[(carg->mem_pos + mem_offset + len - 1 - i) % MEM_SIZE];
		i++;
	}
	return (converter.n);
}

void	put_value(t_arena *arena, int pos, int value)
{
	int			i;
	t_converter	converter;

	i = 0;
	converter.n = value;
	while (i < REG_SIZE)
	{
		arena->map[(pos + REG_SIZE - 1 - i) % MEM_SIZE] = converter.str[i];
		i++;
	}
}

int		get_reg_num(t_arena *arena, int pos)
{
	char	reg_num;

	reg_num = arena->map[pos % MEM_SIZE] % REG_NUMBER;
	reg_num = reg_num != 0 ? reg_num : 16;
	return (reg_num - 1);
}

int		get_arg_len(int oper_type, char arg_type)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (IND_SIZE);
	return (g_op_tab[oper_type].dir_size);
}

/*
**	arg_num 0..2
*/

int		get_args_offset(t_carriage *carg, int arg_num)
{
	int	offset;

	if (arg_num >= g_op_tab[carg->op_id].var_count)
		error_handle(E_INV_ALGO, NULL, "беда в get_args_offset");
	offset = g_op_tab[carg->op_id].kod_tipov_argumenta == 0 ? 1 : 2;
	if (arg_num == 0)
		return (offset);
	offset += get_arg_len(carg->op_id, carg->args[0]);
	if (arg_num == 1)
		return (offset);
	offset += get_arg_len(carg->op_id, carg->args[1]);
	return (offset);
}
