#include "corewar.h"

int		get_value(t_arena *arena, int pos, unsigned char len)
{
	int			i;
	t_converter converter;

	if (len > sizeof(int))
		error_handle(E_INV_ALGO, arena, "беда в get_value");
	converter.n = 0;
	i = 0;
	while (i < len)
	{
		converter.str[i] = arena->map[(pos + len - 1 - i) % MEM_SIZE];
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
		i--;
	}
}

int		get_reg_num(t_arena *arena, int pos)
{
	char	reg_num;

	reg_num = arena->map[pos % MEM_SIZE] % REG_NUMBER;
	reg_num = reg_num != 0 ? reg_num : 16;
	return (reg_num - 1);
}
