/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:09:03 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:43:05 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_magic(int fd, t_arena *arena)
{
	unsigned int magic;

	magic = 0;
	if (read(fd, &magic, 4) != 4 || magic != 4085508608)
		error_handle(E_INV_CHAMP, arena, "bad magic");
}

void	check_null(int fd, t_arena *arena)
{
	unsigned int nulls;

	nulls = 0;
	if (read(fd, &nulls, 4) != 4 || nulls != 0)
		error_handle(E_INV_CHAMP, arena, "zero section is not empty");
}

void	load_player(char *path, t_arena *arena)
{
	t_player	*player;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handle(E_INV_PATH, arena, path);
	player = &(arena->players[get_pnb(arena)]);
	player_ini(player, &arena->flags[F_N]);
	check_magic(fd, arena);
	read_name(fd, player, arena);
	check_null(fd, arena);
	read_code_size(fd, &(player->code_size), arena);
	read_comment(fd, player, arena);
	check_null(fd, arena);
	read_code(fd, player->code_size, player->code, arena);
	arena->players_count++;
	close(fd);
}
