/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:03:50 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/08 18:09:02 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			nb_carg_pos(t_arena *arena, int pos)
{
	t_list		*carg_node;
	t_carriage	*carg;
	int			res;

	res = 0;
	carg_node = arena->carg_lst;
	while (carg_node)
	{
		carg = (t_carriage *)carg_node->content;
		if (carg->mem_pos == pos)
			res++;
		carg_node = carg_node->next;
	}
	return (res);
}

int			plr_pos(int nb)
{
	return (11 + 4 * nb);
}

int			get_color_pair(int pos, t_point p)
{
	int color;
	int i;

	color = mvinch(p.y + pos / 64, p.x + 3 * (pos % 64)) & A_COLOR;
	i = 0;
	while (i < COLOR_PAIRS - 1)
	{
		if (color == COLOR_PAIR(i))
			return (i);
		i++;
	}
	return (-1);
}

void		speed_n_exit(int *speed, char temp)
{
	if (temp == 'q' && *speed > 100)
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
}

void		vis_pause(t_arena *arena, int *pause, int *speed, int *nb)
{
	char temp;

	temp = getch();
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
	else if (temp == 9)
	{
		arena->debug = 1;
		*nb = (*nb + 1) % ft_lstlen(arena->carg_lst);
		carg_info(arena, *nb);
	}
	speed_n_exit(speed, temp);
	refresh();
	if (*pause)
		vis_pause(arena, pause, speed, nb);
}
