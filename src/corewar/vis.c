/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:00:56 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/09 16:11:51 by hharvey          ###   ########.fr       */
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

void		carg_info(t_arena *arena, int nb)
{
	t_list		*clist;
	t_carriage	*cg;
	int			i;
	int			pos;

	clist = arena->carg_lst;
	while (nb && clist)
	{
		clist = clist->next;
		nb--;
	}
	if (clist)
	{
		cg = (t_carriage*)clist->content;
		pos = plr_pos(arena->players_count) + 14;
		color_set(10, NULL);
		mvprintw(pos, POS_TEXT, "                   ");
		mvprintw(pos++, POS_TEXT, arena->players[cg->owner - 1].name);
		i = -1;
		while (++i < 16)
			print_nb(cg->reg[i], pos + i, POS_TEXT, 10);
		print_nb(cg->carry, pos + i + 1, POS_TEXT, 10);
		print_nb(cg->carg_id, pos + i + 2, POS_TEXT, 10);
	}
}
