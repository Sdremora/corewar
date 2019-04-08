/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_reader.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:47 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:42:56 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	read_name(int fd, t_player *player, t_arena *arena)
{
	if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		error_handle(E_INV_CHAMP, arena,
		"the program code of the player is too short");
}

int		swap_int_bytes(unsigned int nb)
{
	int	res;

	res = nb >> 24;
	res |= (nb >> 8) & 0xff00;
	res |= (nb << 8) & 0xff0000;
	res |= (nb << 24);
	return (res);
}

void	read_code_size(int fd, int *p, t_arena *arena)
{
	int size;

	size = 0;
	if (read(fd, &size, 4) != 4)
		error_handle(E_INV_CHAMP, arena, "invalid size");
	*p = swap_int_bytes(size);
	return ;
}

void	read_comment(int fd, t_player *player, t_arena *arena)
{
	if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		error_handle(E_INV_CHAMP, arena,
		"the program code of the player is too short");
}

void	read_code(int fd, int size, char *code, t_arena *arena)
{
	int		len;

	len = read(fd, code, COMMENT_LENGTH);
	if (len < 0)
		error_handle(E_INV_CHAMP, arena,
		"the program code of the player is too short");
	if (len != size)
		error_handle(E_INV_CHAMP, arena,
		"program size is not equal to the specified value");
	if (read(fd, code, 10) > 0 || len > CHAMP_MAX_SIZE)
		error_handle(E_INV_CHAMP, arena,
		"the program code of the player is too long");
	return ;
}
