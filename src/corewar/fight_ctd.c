/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight_ctd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 20:09:19 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/06 20:26:16 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ctd_printf(t_arena *arena, t_carriage *carg)
{
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		carg->carg_id, arena->cur_cycle - carg->last_live_cycle,
		arena->cycle_to_die);
}

void		check_live(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;
	t_list		*temp;

	ft_bzero(arena->player_live_in_cp, sizeof(int) * MAX_PLAYERS);
	carg_node = arena->carg_lst;
	while (carg_node)
	{
		carg = (t_carriage *)carg_node->content;
		if (arena->cycle_to_die <= 0 || !carg->live)
		{
			if (arena->flags[F_VIS])
				remove_carg(arena, carg->mem_pos);
			temp = carg_node->next;
			if (arena->flags[F_V] & 8)
				ctd_printf(arena, carg);
			arena->carg_lst = ft_lstdelsave(arena->carg_lst,
				carg_node, ft_lstdelfun);
			carg_node = temp;
			continue ;
		}
		else
			carg->live = 0;
		carg_node = carg_node->next;
	}
}

void		check_cycle_to_die(t_arena *arena)
{
	int i;

	if (arena->live_call_count >= NBR_LIVE || arena->checks >= MAX_CHECKS)
	{
		arena->cycle_to_die -= CYCLE_DELTA;
		if (arena->flags[F_V] & 2)
			ft_printf("Cycle to die is now %d\n", arena->cycle_to_die);
		arena->checks = 1;
		if (arena->flags[F_VIS])
			print_nb(arena->cycle_to_die,
				plr_pos(arena->players_count) + 6, POS_NB, 10);
	}
	else
		arena->checks++;
	if (arena->flags[F_VIS])
	{
		print_nb(arena->checks, plr_pos(arena->players_count) + 8, POS_NB, 10);
		i = -1;
		while (++i < arena->players_count)
			print_nb(arena->player_live_in_cp[i], plr_pos(i) + 2, POS_NB, 10);
		print_nb(ft_lstlen(arena->carg_lst), 9, POS_NB, 10);
	}
	arena->live_call_count = 0;
}

void		fight_ctd(t_arena *arena)
{
	arena->cycle_past_check -= arena->cycle_to_die;
	check_live(arena);
	check_cycle_to_die(arena);
}
