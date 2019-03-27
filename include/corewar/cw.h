
#ifndef CW_H
#define CW_H

#define REVERSE_MAGIC 4085508608

#include "general/op.h"

#define FLAGS_COUNT 8
#define E_NO_MEMORY -1
#define E_NO_PLAYERS -2
#define E_OVER_PLAYERS -3
#define E_INV_PATH -4
#define E_INV_CHAMP -5
#define E_PLAYER_NUMBER -6
#define E_INV_ALGO -99

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
}				t_carriage;

typedef enum	e_flag
{
	F_A,
	F_B,
	F_STEALTH,
	F_VIS,
	F_D,
	F_S,
	F_V,
	F_N,
}				t_flag;

typedef struct	s_arena
{
	unsigned char	map[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				players_count;
	int				cycle_to_die;
	int				cur_cycle;
	int				cycle_past_check;
	int				checks;
	t_list			*carg_lst;
	int				last_live_player;
	int				live_call_count;
	int				flags[FLAGS_COUNT];
}				t_arena;

typedef union	u_converter
{
	int		n;
	char	str[sizeof(int)];
}				t_converter;

//	main.c
void		print_usage(void);

//	fight.c
void		fight(t_arena *arena);

//	print_map.c
void		print_map(unsigned char *map, int n);

//	load_players.c
void		load_player(char *path, t_arena *arena);

//	load_arena.c
void		load_arena(int argc, char **argv, t_arena *arena);
int			get_pnb(t_arena *arena);

//	arena_utils.c
void		arena_ini(t_arena *arena);
void		arena_clear(t_arena *arena);
void		arena_print(t_arena *arena);

//	errors.c
void		error_handle(int error_id, t_arena *arena, char *addition);

//	player_utils.c
void		player_ini(t_player *player, int player_id);

//	carg_utils.c
t_carriage	*carg_new(int pos, int owner, int cycle);
t_carriage	*carriage_copy(t_carriage *carg);
void		carriage_free(t_carriage **carg);

//	oper_p1.c
void		op_live(t_carriage *carg, t_arena *arena);
void		op_ld_lld(t_carriage *carg, t_arena *arena);
void		op_st(t_carriage *carg, t_arena *arena);
void		op_add_sub(t_carriage *carg, t_arena *arena);
void		op_and_or_xor(t_carriage *carg, t_arena *arena);

//	oper_p2.c
void		op_zjmp(t_carriage *carg, t_arena *arena);
void		op_ldi_lldi(t_carriage *carg, t_arena *arena);
void		op_sti(t_carriage *carg, t_arena *arena);
void		op_fork(t_carriage *carg, t_arena *arena);
void		op_aff(t_carriage *carg, t_arena *arena);
void		op_invalid(t_carriage *carg, t_arena *arena);

//	oper_utils.c
int			get_value(t_arena *arena, int mem_pos, int	len);
void		put_value(t_arena *arena, int pos, int value);
int			get_reg_num(t_arena *arena, int pos);
int			get_arg_len(int oper_type, char arg_type);
int			get_args_offset(t_carriage *carg, int arg_num);
int			read_arg(t_arena *arena, t_carriage *carg, int arg_num, int is_idx_mod);
#endif