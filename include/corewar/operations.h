/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:11:03 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:11:05 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H
# include "corewar.h"

typedef enum	e_oper
{
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
	INVALID
}				t_oper;

typedef struct	s_op
{
	char			name[10];
	int				var_count;
	unsigned char	args[3];
	int				cost;
	int				kod_tipov_argumenta;
	int				dir_size;
	int				is_idx_mod;
	void			(*op_handler)(t_carriage *carg, t_arena *arena);
}				t_op;

extern t_op		g_op_tab[16];

#endif
