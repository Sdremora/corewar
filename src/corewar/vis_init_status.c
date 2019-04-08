/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:28:06 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/06 19:54:14 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_after_player(t_arena *arena)
{
	int pos;

	pos = plr_pos(arena->players_count);
	mvaddstr(pos, POS_TEXT, "Live breakdown for current period :");
	mvaddstr(pos + 1, POS_TEXT, "[------------------------------------------]");
	mvaddstr(pos + 3, POS_TEXT, "Live breakdown for last period :");
	mvaddstr(pos + 4, POS_TEXT, "[------------------------------------------]");
	mvaddstr(pos + 6, POS_TEXT, "Cycle to die :");
	print_nb(arena->cycle_to_die, plr_pos(arena->players_count) + 6,
		POS_NB, 10);
	mvaddstr(pos + 8, POS_TEXT, "Number checks :");
	print_nb(arena->checks, pos + 8, POS_NB, 10);
}

void		draw_status(t_arena *arena)
{
	int i;

	color_set(10, NULL);
	mvaddstr(2, POS_TEXT, "** PAUSED **");
	mvaddstr(5, POS_TEXT, "Cycles/second limit :");
	mvaddstr(5, POS_NB, "50");
	mvaddstr(7, POS_TEXT, "Cycle :");
	mvaddstr(7, POS_NB, "50");
	mvaddstr(9, POS_TEXT, "Processes :");
	print_nb(arena->max_carg_id, 9, POS_NB, 10);
	i = 0;
	while (i < arena->max_carg_id)
	{
		mvaddstr(11 + 4 * i, POS_TEXT, "Player -1 :");
		mvaddch(11 + 4 * i, 209, '0' + i + 1);
		mvaddclrstr(11 + 4 * i, POS_TEXT + 12, i + 1, arena->players[i].name);
		mvaddstr(11 + 4 * i + 1, 203, "Last live :");
		mvaddstr(11 + 4 * i + 1, POS_NB, "0");
		mvaddstr(11 + 4 * i + 2, 203, "Current lives :");
		mvaddstr(11 + 4 * i + 2, POS_NB, "0");
		i++;
	}
	draw_after_player(arena);
}
