/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:55:36 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/08 10:07:18 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carriage	*carg_new(int pos, int owner, int cycle, int carg_id)
{
	t_carriage	*res;

	res = (t_carriage*)malloc(sizeof(t_carriage));
	ft_bzero(res->reg, (REG_NUMBER) * sizeof(int));
	res->reg[0] = owner * -1;
	res->pause_count = 0;
	res->mem_pos = looping(pos);
	res->owner = owner;
	res->carry = 0;
	res->op_id = FALSE_OP;
	res->live = 0;
	res->last_live_cycle = cycle;
	ft_bzero(res->args, 3 * sizeof(int));
	res->carg_id = carg_id;
	return (res);
}

t_carriage	*carriage_copy(t_carriage *carg, int new_id)
{
	t_carriage *new_carg;

	new_carg = carg_new(carg->mem_pos, carg->owner,
					carg->last_live_cycle, new_id);
	if (new_carg == NULL)
		return (NULL);
	ft_memcpy(new_carg->reg, carg->reg, REG_NUMBER * sizeof(int));
	new_carg->live = carg->live;
	new_carg->carry = carg->carry;
	return (new_carg);
}

void		carriage_free(t_carriage **carg)
{
	free(*carg);
	*carg = NULL;
}
