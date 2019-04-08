/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:25:28 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/08 09:56:59 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_color_pairs(void)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, 8);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, 15, COLOR_BLACK);
}

void		draw_map(unsigned char *str, t_point p)
{
	int			i;
	static char	base[17] = "0123456789abcdef";

	color_set(0, NULL);
	i = 0;
	while (i < MEM_SIZE)
	{
		mvaddch(p.y + i / 64, p.x + 3 * (i % 64), base[str[i] / 16 % 16]);
		mvaddch(p.y + i / 64, p.x + 3 * (i % 64) + 1, base[str[i] % 16]);
		i++;
	}
}

void		draw_box(void)
{
	int i;

	i = 0;
	color_set(5, NULL);
	while (i < 250)
	{
		mvaddch(0, i, ' ');
		mvaddch(67, i, ' ');
		i++;
	}
	i = 0;
	while (i < 67)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, 1, ' ');
		mvaddch(i, 197, ' ');
		mvaddch(i, 198, ' ');
		mvaddch(i, 248, ' ');
		mvaddch(i, 249, ' ');
		i++;
	}
}

void		draw_players(t_arena *arena)
{
	int			i;
	int			pos;
	static char	base[17] = "0123456789abcdef";
	int			max_pos;

	i = 0;
	while (i < arena->players_count)
	{
		color_set(i + 1 + 5, NULL);
		pos = i * MEM_SIZE / arena->players_count;
		max_pos = pos + arena->players[i].code_size;
		if (pos == max_pos)
			draw_pos(arena, 5, pos);
		while (pos < max_pos)
		{
			mvaddch(arena->shift.y + pos / 64,
		arena->shift.x + 3 * (pos % 64), base[arena->map[pos] / 16 % 16]);
			mvaddch(arena->shift.y + pos / 64,
		arena->shift.x + 3 * (pos % 64) + 1, base[arena->map[pos] % 16]);
			if (pos == i * MEM_SIZE / arena->players_count)
				color_set(i + 1, NULL);
			pos++;
		}
		i++;
	}
}

void		arena_vis_init(t_arena *arena, int *speed, int *pause)
{
	int x;
	int y;

	x = 4;
	y = 2;
	arena->shift = ft_pnt(x, y);
	initscr();
	assume_default_colors(8, COLOR_BLACK);
	noecho();
	set_color_pairs();
	draw_map(arena->map, arena->shift);
	draw_box();
	draw_status(arena);
	draw_players(arena);
	curs_set(0);
	refresh();
	*speed = 20000;
	*pause = 1;
}
