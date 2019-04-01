#include "corewar.h"

int		get_arg_len(int oper_type, char arg_type)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (IND_SIZE);
	return (g_op_tab[oper_type].dir_size);
}

static int	get_arg_value_len(int oper_type, char arg_type)
{
	int len;

	if (arg_type == T_REG)
		len = REG_SIZE;
	else if (arg_type == T_IND)
		len = IND_SIZE;
	else
		len = g_op_tab[oper_type].dir_size;
	return (len);
}

int		get_value(t_arena *arena, int mem_pos, int	len)
{
	int			i;
	int			k;
	t_converter converter;

	converter.n = 0;
	i = 0;
	k = len - 1;
	while (i < len)
	{
		converter.str[i] = arena->map[get_pos(mem_pos + k)];
		i++;
		k--;
	}
	if (len != REG_SIZE && (converter.n >> (len * 8 - 1)) == 1)
		converter.n = converter.n | ((~0x0) << len * 8);
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
		arena->map[get_pos(pos + REG_SIZE - 1 - i)] = converter.str[i];
		i++;
	}
}

int		get_reg_num(t_arena *arena, int pos)
{
	char	reg_num;

	reg_num = arena->map[get_pos(pos)];
	if (reg_num >= 1 && reg_num <= REG_NUMBER)
		return (reg_num - 1);
	return (-1);
}

/*
**	arg_num 0..2
*/

int		get_args_offset(t_carriage *carg, t_arg_num arg_num)
{
	int	offset;

	offset = g_op_tab[carg->op_id].kod_tipov_argumenta == 0 ? 1 : 2;
	if (arg_num == ARG_1)
		return (offset);
	offset += get_arg_len(carg->op_id, carg->args[0]);
	if (arg_num == ARG_2)
		return (offset);
	offset += get_arg_len(carg->op_id, carg->args[1]);
	if (arg_num == ARG_3)
		return (offset);
	offset += get_arg_len(carg->op_id, carg->args[2]);
	return (offset);
}

int		read_arg(int *value, t_arena *arena, t_carriage *carg, t_arg_num arg_num)
{
	int	arg_type;
	int offset;
	int	reg_num;

	arg_type = carg->args[arg_num];
	offset = get_args_offset(carg, arg_num);
	if (arg_type == T_REG)
	{
		reg_num = get_reg_num(arena, carg->mem_pos + offset);
		if (reg_num < 0)
			return (-1);
		*value = carg->reg[reg_num];
	}
	else if (arg_type == T_DIR)
		*value = get_value(arena, carg->mem_pos + offset, g_op_tab[carg->op_id].dir_size);
	else
	{
		offset = get_value(arena, carg->mem_pos + offset, IND_SIZE) % IDX_MOD;
		*value = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	}
	return (0);
}

int	get_pos(int index)
{
	int	pos;

	pos = index % MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}
