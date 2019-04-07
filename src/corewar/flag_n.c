/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:42:50 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/06 18:04:17 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		add_swap_players(t_arena *arena, int pos)
{
	int			i;
	t_player	temp;

	i = 0;
	while (i < pos && arena->players[i].id > arena->players[pos].id)
		i++;
	if (i == pos)
		return ;
	else
	{
		temp = arena->players[pos];
		arena->players[pos] = arena->players[i];
		arena->players[i] = temp;
	}
	add_swap_players(arena, i);
}

void		swap_players(t_arena *arena, int pos)
{
	int			i;
	t_player	temp;

	i = 0;
	while (i < MAX_PLAYERS && arena->players[i].id != -1)
		i++;
	if (i == MAX_PLAYERS)
		error_handle(E_PLAYER_NUMBER, arena, NULL);
	temp = arena->players[pos];
	arena->players[pos] = arena->players[i];
	arena->players[i] = temp;
	add_swap_players(arena, i);
}

int			get_pnb(t_arena *arena)
{
	int	i;

	if ((i = arena->flags[F_N]) != -1)
	{
		i--;
		if (i >= 0 && i < MAX_PLAYERS && arena->players[i].id < 0)
		{
			if (arena->players[i].id < -1)
				swap_players(arena, i);
			return (i);
		}
		else
			error_handle(E_PLAYER_NUMBER, arena, NULL);
	}
	i = 0;
	while (arena->players[i].id != -1)
		i++;
	return (i);
}
