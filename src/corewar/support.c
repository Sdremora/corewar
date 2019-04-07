/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:09:06 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:09:08 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		introducing(t_arena *arena)
{
	int			i;
	t_player	player;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < arena->players_count)
	{
		player = arena->players[i];
		i++;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i, player.code_size, player.name, player.comment);
	}
}
