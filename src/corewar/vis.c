/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:00:56 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/05 18:17:35 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		draw_pos(t_arena *arena, int color, int pos)
{
	static char base[17] = "0123456789abcdef";

	color_set(color, NULL);
	mvaddch(arena->shift.y + pos / 64, arena->shift.x + 3 * (pos % 64),
			base[arena->map[pos] / 16 % 16]);
	mvaddch(arena->shift.y + pos / 64, arena->shift.x + 3 * (pos % 64) + 1,
			base[arena->map[pos] % 16]);
}

void		remove_carg(t_arena *arena, int pos)
{
	int color;

	if ((color = get_color_pair(pos, arena->shift)) > 4
		&& nb_carg_pos(arena, pos) == 1)
	{
		draw_pos(arena, color - 5, pos);
	}
}

void		print_nb(int nb, int y, int x, int col_nb)
{
	char *str;

	str = ft_itoa(nb);
	color_set(col_nb, NULL);
	mvaddstr(y, x, "          ");
	mvaddstr(y, x, str);
	free(str);
}

void		mvaddclrstr(int y, int x, int col_nb, char *str)
{
	color_set(col_nb, NULL);
	mvaddstr(y, x, str);
	color_set(10, NULL);
}
