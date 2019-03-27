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
		converter.str[i] = arena->map[(mem_pos + k) % MEM_SIZE];
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

int		read_arg(t_arena *arena, t_carriage *carg, int arg_num, int is_idx_mod)
{
	int	value;
	int	arg_type;
	int offset;

	arg_type = carg->args[arg_num];
	offset = get_args_offset(carg, arg_num);
	if (arg_type == T_REG)
		value = carg->reg[get_reg_num(arena, carg->mem_pos + offset)];
	else if (arg_type == T_DIR)
		value = get_value(arena, carg->mem_pos + offset, g_op_tab[carg->op_id].dir_size);
	else
	{
		offset = get_value(arena, carg->mem_pos + offset, IND_SIZE);
		offset = is_idx_mod == TRUE ? offset % IDX_MOD : offset;
		value = get_value(arena, carg->mem_pos + offset, REG_SIZE);
	}
	return (value);
}