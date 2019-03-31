/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:00:56 by hharvey           #+#    #+#             */
/*   Updated: 2019/03/31 17:27:52 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_color_pair(int pos, t_point p)
{
	int color;
	int i;

	color = mvinch(p.y + pos / 64, p.x +  3 * (pos % 64)) & A_COLOR;
	i = 0;
	while (i < COLOR_PAIRS - 1)
	{
		if (color == COLOR_PAIR(i))
			return (i);
		i++;
	}
	return (-1);
}

void		draw_pos(t_arena *arena, int color, int pos)
{
	static char base[17] = "0123456789abcdef";

	color_set(color, NULL);
	mvaddch(arena->shift.y + pos / 64, arena->shift.x +  3 * (pos % 64), base[arena->map[pos] / 16 % 16]);
	mvaddch(arena->shift.y + pos / 64, arena->shift.x + 3 * (pos % 64) + 1, base[arena->map[pos] % 16]);
}

void		remove_carg(t_arena *arena, int pos)
{
	int color;

	if ((color = get_color_pair(pos, arena->shift)) > 4 && nb_carg_pos(arena, pos) == 1)
	{
		draw_pos(arena, color - 5, pos);
	}
}

void		print_nb(int nb, int y, int x)
{
	char *str;

	str = ft_itoa(nb);
	mvaddstr(y, x, str);
	free(str);
}