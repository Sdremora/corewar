/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/24 13:19:54 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[15] =
{
	{"live", 1, {T_DIR}, 10, 0, 0, op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 0, op_load},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
	{"zjmp", 1, {T_DIR}, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 1},
	{"fork", 1, {T_DIR}, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 1},
	{"lfork", 1, {T_DIR}, 1000, 0, 1},
	{"aff", 1, {T_REG}, 2, 1, 0},
};
