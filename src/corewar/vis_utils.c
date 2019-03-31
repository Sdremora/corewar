/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:03:50 by hharvey           #+#    #+#             */
/*   Updated: 2019/03/31 17:04:31 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			nb_carg_pos(t_arena *arena, int pos)
{
	t_list *carg_node;
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