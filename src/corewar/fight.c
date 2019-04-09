/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:26 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/09 16:15:25 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		fight_vis(t_arena *arena)
{
	int		speed;
	int		pause;
	int		nb;

	nb = 0;
	introducing(arena);
	arena_vis_init(arena, &speed, &pause);
	while (arena->carg_lst)
	{
		print_nb(arena->cur_cycle, 7, POS_NB, 10);
		if (arena->debug)
			carg_info(arena, nb);
		vis_pause(arena, &pause, &speed, &nb);
		usleep(speed);
		arena->cur_cycle++;
		arena->cycle_past_check++;
		play_round(arena);
		if (arena->cycle_past_check == arena->cycle_to_die
			|| arena->cycle_to_die <= 0)
		{
			draw_breakdown(arena->player_live_in_cp, arena->players_count, 3);
			fight_ctd(arena);
			draw_breakdown(arena->player_live_in_cp, arena->players_count, 0);
		}
	}
}

void		fight(t_arena *arena)
{
	introducing(arena);
	while (arena->carg_lst)
	{
		if (arena->cur_cycle == arena->flags[F_D])
			return (print_map(arena->map, 64));
		if (arena->cur_cycle == arena->flags[F_DUMP])
			return (print_map(arena->map, 32));
		if (arena->cur_cycle == arena->flags[F_S] && arena->flags[F_S] > 0)
		{
			print_map(arena->map, 64);
			read(0, 0, 1);
			arena->flags[F_S] += arena->flags[F_STEALTH];
		}
		arena->cur_cycle++;
		if (arena->flags[F_V] & 2)
			ft_printf("It is now cycle %d\n", arena->cur_cycle);
		arena->cycle_past_check++;
		play_round(arena);
		if (arena->cycle_past_check == arena->cycle_to_die
			|| arena->cycle_to_die <= 0)
			fight_ctd(arena);
	}
}
