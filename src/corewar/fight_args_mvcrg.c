/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight_args_mvcrg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:30 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:55:20 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_code_args(int args[3], unsigned char op_id)
{
	int i;

	i = 0;
	while (i < 3 && g_op_tab[op_id].args[i])
	{
		if (!(args[i] & g_op_tab[op_id].args[i]))
			return (0);
		i++;
	}
	return (1);
}

int			step_bites(int arg, int dir_size)
{
	if (arg == T_REG)
		return (1);
	if (arg == T_DIR)
		return (dir_size);
	if (arg == T_IND)
		return (2);
	if (arg == 0)
		return (0);
	return (-42);
}

int			convert_args(unsigned char arg)
{
	if (arg == REG_CODE)
		return (T_REG);
	if (arg == DIR_CODE)
		return (T_DIR);
	if (arg == IND_CODE)
		return (T_IND);
	return (0);
}

void		load_args(t_carriage *carg, t_arena *arena)
{
	unsigned char	arg;
	int				i;

	if (g_op_tab[carg->op_id].kod_tipov_argumenta)
	{
		i = 0;
		arg = arena->map[looping(carg->mem_pos + 1)];
		while (i < 3 && g_op_tab[carg->op_id].args[i])
		{
			carg->args[i] = convert_args(arg >> (6 - 2 * i) & 3);
			i++;
		}
	}
	else
		carg->args[0] = T_DIR;
}

void		move_carriage(t_arena *arena, t_carriage *carg, int dir_size)
{
	int move;
	int	next_pos;
	int i;

	if (carg->op_id == ZJMP && carg->carry == 1)
		return ;
	i = 0;
	move = 1 + g_op_tab[carg->op_id].kod_tipov_argumenta;
	while (i < 3 && g_op_tab[carg->op_id].args[i])
		move += step_bites(carg->args[i++], dir_size);
	next_pos = looping(carg->mem_pos + move);
	if (arena->flags[F_V] & 16)
	{
		ft_printf("ADV %d (%06p -> %06p) ", move, carg->mem_pos, next_pos);
		i = 0;
		while (i < move)
		{
			ft_printf("%02x ", arena->map[looping(carg->mem_pos + i)]);
			i++;
		}
		ft_putchar('\n');
	}
	carg->mem_pos = next_pos;
}
