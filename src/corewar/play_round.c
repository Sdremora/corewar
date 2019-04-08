/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_round.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:26:08 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/08 10:09:24 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vis_move_carg(int old, int new, t_arena *arena)
{
	int color;

	if ((color = get_color_pair(old, arena->shift)) > 4
		&& !nb_carg_pos(arena, old))
	{
		draw_pos(arena, color - 5, old);
	}
	if ((color = get_color_pair(new, arena->shift)) < 5)
	{
		draw_pos(arena, color + 5, new);
	}
}

void	operations_handle(t_carriage *carg, t_arena *arena)
{
	unsigned char	oper;

	oper = arena->map[carg->mem_pos] - 1;
	if (oper >= LIVE && oper <= AFF)
	{
		carg->pause_count = g_op_tab[oper].cost;
		carg->op_id = oper;
	}
	else
		carg->mem_pos = looping(carg->mem_pos + 1);
}

void	do_op(t_arena *arena, t_carriage *carg)
{
	load_args(carg, arena);
	if (!g_op_tab[carg->op_id].kod_tipov_argumenta
	|| check_code_args(carg->args, carg->op_id))
		g_op_tab[carg->op_id].op_handler(carg, arena);
	move_carriage(arena, carg, g_op_tab[carg->op_id].dir_size);
	carg->op_id = FALSE_OP;
	ft_bzero(carg->args, sizeof(int) * 3);
}

void	play_round(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;
	int			cur_pos;

	carg_node = arena->carg_lst;
	while (carg_node)
	{
		carg = (t_carriage *)carg_node->content;
		cur_pos = carg->mem_pos;
		if (carg->op_id == FALSE_OP)
			operations_handle(carg, arena);
		if (carg->pause_count > 0)
			carg->pause_count--;
		if (carg->op_id != FALSE_OP && carg->pause_count == 0)
			do_op(arena, carg);
		if (arena->flags[F_VIS])
			vis_move_carg(looping(cur_pos), looping(carg->mem_pos), arena);
		carg_node = carg_node->next;
	}
}
