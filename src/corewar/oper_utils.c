#include "corewar.h"

int		get_dir_value(t_arena *arena, int pos, int dir_size)
{
	int			i;
	t_converter converter;

	converter.n = 0;
	i = 0;
	while (i < dir_size)
	{
		converter.str[i] = arena->map[(pos + dir_size - 1 - i) % MEM_SIZE];
		i++;
	}
	return (converter.n);
}

int		get_ind_value(t_arena *arena, int pos)
{
	t_converter converter;

	converter.str[0] = arena->map[(pos + 1) % MEM_SIZE];
	converter.str[1] = arena->map[pos % MEM_SIZE];
	converter.str[2] = 0;
	converter.str[3] = 0;
	return (get_dir_value(arena, pos + converter.n, REG_SIZE));
}

int		get_reg_num(t_arena *arena, int pos)
{
	char	reg_num;

	reg_num = arena->map[pos % MEM_SIZE] % REG_NUMBER;
	reg_num = reg_num != 0 ? reg_num : 16;
	return (reg_num - 1);
}
