/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:14:41 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/07 18:48:49 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include "general/op.h"
# include <curses.h>

# define REVERSE_MAGIC 4085508608

# define FLAGS_COUNT 8
# define E_NO_MEMORY -1
# define E_NO_PLAYERS -2
# define E_OVER_PLAYERS -3
# define E_INV_PATH -4
# define E_INV_CHAMP -5
# define E_PLAYER_NUMBER -6
# define E_INV_ALGO -99

# define POS_NB 235
# define POS_TEXT 201

# define BD_LEN 42

typedef struct	s_player
{
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH + 1];
	char	code[CHAMP_MAX_SIZE];
	int		code_size;
	int		id;
}				t_player;

typedef struct	s_carriage
{
	int				reg[REG_NUMBER];
	int				pause_count;
	int				mem_pos;
	int				owner;
	int				carry;
	char			op_id;
	int				live;
	int				last_live_cycle;
	int				args[3];
	int				carg_id;
}				t_carriage;

typedef enum	e_flag
{
	F_A,
	F_B,
	F_STEALTH,
	F_VIS,
	F_D,
	F_S,
	F_N,
	F_V,
}				t_flag;

typedef struct	s_arena
{
	unsigned char	map[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				player_live_in_cp[MAX_PLAYERS];
	int				players_count;
	int				cycle_to_die;
	int				cur_cycle;
	int				cycle_past_check;
	int				checks;
	t_list			*carg_lst;
	int				last_live_player;
	int				live_call_count;
	int				flags[FLAGS_COUNT];
	int				max_carg_id;
	t_point			shift;
}				t_arena;

typedef union	u_converter
{
	int		n;
	char	str[sizeof(int)];
}				t_converter;

typedef enum	e_arg_num
{
	ARG_1,
	ARG_2,
	ARG_3
}				t_arg_num;

#endif
