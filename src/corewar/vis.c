/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:00:56 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/05 17:40:14 by hharvey          ###   ########.fr       */
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

void		vis_pause(int *pause, int *speed)
{
	char temp;

	temp = getch();
//	print_nb(temp, 1, 0, 10);
	if (temp == 32 && !(*pause))
	{
		timeout(-1);
		mvaddclrstr(2, POS_TEXT, 10, "** PAUSED ** ");
		*pause = 1;
	}
	else if (temp == 32)
	{
		timeout(0);
		mvaddclrstr(2, POS_TEXT, 10, "** RUNNING **");
		*pause = 0;
	}
	else if (temp == 'q' && *speed > 100)
		*speed = 1000000 / (10 + 1000000 / (*speed));
	else if (temp == 'w' && *speed < 100000)
		*speed = 1000000 / (-10 + 1000000 / (*speed));
	else if (temp == 'a' && *speed > 100)
		*speed = 1000000 / (1 + 1000000 / (*speed));
	else if (temp == 's' && *speed < 999999)
		*speed = 1000000 / (-1 + 1000000 / (*speed));
	else if (temp == 27)
	{
		endwin();
		exit(1);
	}
	if (temp == 'q' || temp == 'w' || temp == 'a' || temp == 's')
		print_nb(1000000 / *speed, 5, POS_NB, 10);
	refresh();
	if (*pause)
		vis_pause(pause, speed);
}

void		draw_term_bd(int arr[MAX_PLAYERS], int pnb, int step)
{
	int i;
	int pos;
	int j;

	pos = POS_TEXT + 1;
	i = 0;

	while (i < pnb)
	{
		j = 0;
		color_set(i + 1, NULL);
		while (j < arr[i])
		{
			mvaddch(plr_pos(pnb) + 1 + step, pos, '-');
			j++;
			pos++;
		}
		i++;
	}
}

void		draw_empty_bd(int step, int pnb)
{
	mvaddstr(plr_pos(pnb) + 1 + step, POS_TEXT,"[------------------------------------------]");
}

void		draw_breakdown(int lnb[MAX_PLAYERS], int nb, int pnb, int step)
{
	int wght[MAX_PLAYERS];
	int fract[MAX_PLAYERS];
	int s;
	int i;

	s = ft_arrsum(lnb, pnb);
	if (!s)
		return draw_empty_bd(step, pnb);
	i = 0;
	while (i < pnb)
	{
		wght[i] = lnb[i] * nb / s;
		fract[i] = lnb[i] * nb * 10 / s % 10;
		i++;
	}
	s = nb - ft_arrsum(wght, pnb);
	while (s > 0)
	{
		i = ft_arrposmax(fract, pnb);
		wght[i] += 1;
		fract[i] = 1;
		s--;
	}
	draw_term_bd(wght, pnb, step);
}