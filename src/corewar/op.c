/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:59 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/04 17:41:22 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 10, 0, 4, TRUE, op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 4, TRUE, op_ld_lld},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 4, TRUE, op_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 4, TRUE, op_add_sub},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 4, TRUE, op_add_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, TRUE, op_and_or_xor},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, TRUE, op_and_or_xor},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, TRUE, op_and_or_xor},
	{"zjmp", 1, {T_DIR}, 20, 0, 2, TRUE, op_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		25, 1, 2, TRUE, op_ldi_lldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		25, 1, 2, TRUE, op_sti},
	{"fork", 1, {T_DIR}, 800, 0, 2, TRUE, op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 4, FALSE, op_ld_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		50, 1, 2, FALSE, op_ldi_lldi},
	{"lfork", 1, {T_DIR}, 1000, 0, 2, FALSE, op_fork},
	{"aff", 1, {T_REG}, 2, 1, 4, TRUE, op_aff},
};
