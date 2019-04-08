/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:52 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/08 10:22:11 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(void)
{
	ft_printf("./corewar [-d N -v N -a | -s N -v N -a | -vis] \
-n N <champion1.cor> <...>\n");
	ft_printf("  %-16s: Precise indication of the player number (from 1 to \
max champions)\n", "-n N");
	ft_printf("{green}Text output mode{def}\n");
	ft_printf("  %-16s: Prints output from \"aff\" (Default is to hide it)\n",
				"-a");
	ft_printf("  %-16s: Dumps memory after N cycles then exits\n",
				"-d (or -dump) N");
	ft_printf("  %-16s: Runs N cycles, dumps memory, pauses, then repeats\n",
				"-s N");
	ft_printf("  %-16s: Verbosity levels, can be added together to enable \
several\n", "-v N");
	ft_printf("  %-17s - 0 : Show only essentials\n", "");
	ft_printf("  %-17s - 1 : Show lives\n", "");
	ft_printf("  %-17s - 2 : Show cycles\n", "");
	ft_printf("  %-17s - 4 : Show operations (Params are NOT litteral ...)\n",
				"");
	ft_printf("  %-17s - 8 : Show deaths\n", "");
	ft_printf("  %-17s - 16 : Show PC movements (Except for jumps)\n", "");
	ft_printf("  %-17sfor example: -v 11 (1 + 2 + 8) show lives, cycles and \
deaths\n", "");
	ft_printf("{green}Ncurses output mode (visualization){def}\n");
	ft_printf("  %-16s: Ncurses output mode\n", "-vis");
	exit(0);
}

void	print_winner(t_arena *arena)
{
	if (arena->flags[F_D] > 0 && arena->carg_lst != NULL)
		return ;
	ft_printf("🚨  Contestant %d, \"%s\", has won ! 🚨\n",
		arena->last_live_player + 1,
		arena->players[arena->last_live_player].name);
}

int		main(int argc, char **argv)
{
	t_arena		arena;

	setlocale(LC_ALL, "en_US.UTF-8");
	if (argc == 1)
		print_usage();
	load_arena(argc, argv, &arena);
	if (arena.flags[F_VIS])
		fight_vis(&arena);
	else
		fight(&arena);
	if (arena.flags[F_VIS])
	{
		timeout(-1);
		mvaddstr(plr_pos(arena.players_count) + 10,
		POS_TEXT, "The winner is :");
		mvaddclrstr(plr_pos(arena.players_count) + 10,
			POS_TEXT + 16, arena.last_live_player + 1,
				arena.players[arena.last_live_player].name);
		mvaddstr(plr_pos(arena.players_count) + 12,
			POS_TEXT, "Press any key to finish");
		getch();
		endwin();
	}
	print_winner(&arena);
	return (0);
}
