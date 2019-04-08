/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:59 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:09:00 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	locate_players(t_arena *arena)
{
	int			i;
	int			pos;
	t_carriage	*carriage;
	t_list		*node;

	i = 0;
	while (i < arena->players_count)
	{
		pos = i * MEM_SIZE / arena->players_count;
		ft_memcpy(arena->map + pos,
		arena->players[i].code, arena->players[i].code_size);
		arena->max_carg_id++;
		carriage = carg_new(pos, i + 1, 0, arena->max_carg_id);
		if (carriage == NULL)
			error_handle(E_NO_MEM, arena, NULL);
		node = ft_lstput(carriage, sizeof(t_carriage));
		if (node == NULL)
			error_handle(E_NO_MEM, arena, NULL);
		ft_lstadd(&arena->carg_lst, node);
		i++;
	}
	return ;
}

void		flag_format(int *arr)
{
	int i;

	i = 0;
	arr[F_STEALTH] = arr[F_S];
	if (arr[F_VIS])
	{
		while (i < FLAGS_COUNT)
			arr[i++] = -1;
		arr[F_V] = 0;
		arr[F_VIS] = 1;
	}
}

int			check_players(t_arena *arena)
{
	int i;

	i = 0;
	while (i < arena->players_count)
	{
		if (arena->players[i].id == -1
			|| arena->players[i].id >= arena->players_count)
			return (0);
		i++;
	}
	return (1);
}

void		load_arena(int argc, char **argv, t_arena *arena)
{
	int i;

	arena_ini(arena);
	i = 1;
	while (i < argc)
	{
		if (!handle_flag(argv, &i, argc, arena))
		{
			if (arena->players_count < MAX_PLAYERS)
				load_player(argv[i], arena);
			else
				error_handle(E_OVER_PLAYERS, arena, NULL);
		}
		i++;
	}
	if (arena->players_count == 0 || !check_players(arena))
	{
		arena_clear(arena);
		error_handle(E_PLAYER_NUMBER, arena, NULL);
	}
	arena->last_live_player = arena->players_count - 1;
	flag_format(arena->flags);
	locate_players(arena);
}
