/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_bd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:16:07 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/07 18:03:15 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	color_set(10, NULL);
	mvaddstr(plr_pos(pnb) + 1 + step, POS_TEXT,
	"[------------------------------------------]");
}

void		draw_breakdown(int lnb[MAX_PLAYERS], int pnb, int step)
{
	int wght[MAX_PLAYERS];
	int fract[MAX_PLAYERS];
	int s;
	int i;

	s = ft_arrsum(lnb, pnb);
	if (!s)
		return (draw_empty_bd(step, pnb));
	i = 0;
	while (i < pnb)
	{
		wght[i] = lnb[i] * BD_LEN / s;
		fract[i] = lnb[i] * BD_LEN * 10 / s % 10;
		i++;
	}
	s = BD_LEN - ft_arrsum(wght, pnb);
	while (s > 0)
	{
		i = ft_arrposmax(fract, pnb);
		wght[i] += 1;
		fract[i] = 1;
		s--;
	}
	draw_term_bd(wght, pnb, step);
}
