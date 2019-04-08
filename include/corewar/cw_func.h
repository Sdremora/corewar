/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:37:38 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/08 17:57:58 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_FUNC_H
# define CW_FUNC_H

# include "corewar.h"

/*
**	main.c
*/
void		print_usage(void);

/*
**	fight.c
*/
void		fight(t_arena *arena);
void		fight_vis(t_arena *arena);

/*
**	print_map.c
*/
void		print_mem(unsigned int n);
void		print_map(unsigned char *map, int n);
void		print_octet(unsigned char p);

/*
**	load_players.c
*/
void		load_player(char *path, t_arena *arena);

/*
**	load_arena.c
*/
void		load_arena(int argc, char **argv, t_arena *arena);

/*
**	flag_n.c
*/
int			get_pnb(t_arena *arena);

/*
**	arena_utils.c
*/
void		arena_ini(t_arena *arena);
void		arena_clear(t_arena *arena);
void		arena_print(t_arena *arena);

/*
**	errors.c
*/
void		error_handle(int error_id, t_arena *arena, char *addition);

/*
**	player_utils.c
*/
void		player_ini(t_player *player, int *player_id);

/*
**	carg_utils.c
*/
t_carriage	*carg_new(int pos, int owner, int cycle, int carg_id);
t_carriage	*carriage_copy(t_carriage *carg, int new_id);
void		carriage_free(t_carriage **carg);

/*
**	oper_p1.c
*/
void		op_live(t_carriage *carg, t_arena *arena);
void		op_ld_lld(t_carriage *carg, t_arena *arena);
void		op_st(t_carriage *carg, t_arena *arena);
void		op_add_sub(t_carriage *carg, t_arena *arena);
void		op_and_or_xor(t_carriage *carg, t_arena *arena);

/*
**	oper_p2.c
*/
void		op_zjmp(t_carriage *carg, t_arena *arena);
void		op_ldi_lldi(t_carriage *carg, t_arena *arena);
void		op_sti(t_carriage *carg, t_arena *arena);
void		op_fork(t_carriage *carg, t_arena *arena);
void		op_aff(t_carriage *carg, t_arena *arena);

/*
**	oper_utils_p1.c
*/
int			get_arg_len(int oper_type, char arg_type);
int			get_value(t_arena *arena, int mem_pos, int	len);
int			get_args_offset(t_carriage *carg, t_arg_num arg_num);
int			read_arg(int *value,
			t_arena *arena, t_carriage *carg, t_arg_num arg_num);

/*
**	oper_utils_p2.c
*/
int			get_reg_num(t_arena *arena, int pos);
int			looping(int index);
void		put_value(t_arena *arena, int pos, int value, int pnb);
int			get_pos(t_carriage *carg, t_arg_num arg_num);

/*
**	support.c
*/
void		introducing(t_arena *arena);

/*
**	vis.c
*/
int			get_color_pair(int pos, t_point p);
void		draw_pos(t_arena *arena, int color, int pos);
void		remove_carg(t_arena *arena, int pos);
void		mvaddclrstr(int y, int x, int col_nb, char *str);
void		draw_breakdown(int lnb[MAX_PLAYERS], int pnb, int step);
void		carg_info(t_arena *arena, int nb);

/*
**	vis_utils
*/
int			nb_carg_pos(t_arena *arena, int pos);
void		print_nb(int nb, int y, int x, int clr_nb);
int			plr_pos(int nb);
void		vis_pause(t_arena *arena, int *pause, int *speed, int *nb);

/*
**	flags_handle.c
*/
int			handle_flag(char **argv, int *pos, int argc, t_arena *arena);

/*
**	load_player_reader.c
*/
void		read_name(int fd, t_player *player, t_arena *arena);
void		read_code_size(int fd, int *p, t_arena *arena);
void		read_comment(int fd, t_player *player, t_arena *arena);
void		read_code(int fd, int size, char *code, t_arena *arena);

/*
**vis_init
*/
void		arena_vis_init(t_arena *arena, int *speed, int *pause);

/*
**	fight_args_mvcrg.c
*/
void		move_carriage(t_arena *arena, t_carriage *carg, int dir_size);
void		load_args(t_carriage *carg, t_arena *arena);
int			check_code_args(int args[3], unsigned char op_id);

/*
**play_round
*/
void		play_round(t_arena *arena);

/*
**	vis_init_status
*/
void		draw_status(t_arena *arena);

/*
**	fight_ctd
*/
void		fight_ctd(t_arena *arena);

#endif
