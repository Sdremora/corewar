/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_utils_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:59:41 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/01 18:05:26 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_reg_num(t_arena *arena, int pos)
{
	char	reg_num;

	reg_num = arena->map[looping(pos)];
	if (reg_num >= 1 && reg_num <= REG_NUMBER)
		return (reg_num - 1);
	return (-1);
}

int		looping(int index)
{
	int	pos;

	pos = index % MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

void	put_value(t_arena *arena, int pos, int value, int pnb)
{
	int			i;
	t_converter	converter;
	int			new_pos;

	i = 0;
	converter.n = value;
	while (i < REG_SIZE)
	{
		new_pos = looping(pos + REG_SIZE - 1 - i);
		arena->map[new_pos] = converter.str[i];
		if (arena->flags[F_VIS])
		{
			if (get_color_pair(new_pos, arena->shift) < 5)
				draw_pos(arena, pnb, new_pos);
			else
				draw_pos(arena, pnb + 5, new_pos);
		}
		i++;
	}
}

int		get_pos(t_carriage *carg, t_arg_num arg_num)
{
	return (carg->mem_pos + get_args_offset(carg, arg_num));
}
