/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:09:36 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/01 18:11:15 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	*errorid_to_str(int error_id)
{
	char *msg;

	if (error_id == E_NO_MEMORY)
		msg = ft_strdup("no memory");
	else if (error_id == E_OVER_PLAYERS)
		msg = ft_strdup("too many champions");
	else if (error_id == E_INV_PATH)
		msg = ft_strdup("сan't read source file ");
	else if (error_id == E_INV_CHAMP)
		msg = ft_strdup("mistake in the champion's code ");
	else if (error_id == E_PLAYER_NUMBER)
		msg = ft_strdup("invalid player number");
	else
		msg = ft_strdup("unknown error");
	return (msg);
}

/*
**	addition -> addition to the error code message.
**	if it is not needed, then addition = NULL
*/

void		error_handle(int error_id, t_arena *arena, char *addition)
{
	char	*error_msg;
	char	*add;

	add = NULL;
	if (addition)
		add = ft_strdup(addition);
	arena_clear(arena);
	error_msg = errorid_to_str(error_id);
	if (error_msg == NULL)
		ft_putstr("Error: no memory!\n");
	else
	{
		if (add)
			ft_printf("{red}Error: {def}%s: %s\n", error_msg, add);
		else
			ft_printf("{red}Error: {def}%s\n", error_msg);
	}
	free(error_msg);
	free(add);
	exit(error_id);
}
