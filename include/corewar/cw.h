
#ifndef CW_H
#define CW_H

#define REVERSE_MAGIC 4085508608

#include "general/op.h"

#define FLAGS_COUNT 7
#define E_NO_MEMORY -1
#define E_NO_PLAYERS -2
#define E_OVER_PLAYERS -3
#define E_INV_PATH -4
#define E_INV_CHAMP -5

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
	int		reg[REG_NUMBER];
	int		pause_count;
	int		mem_pos;
	int		owner;
}				t_carriage;

typedef enum	e_flag
{
	F_A,
	F_D,
	F_S,
	F_V,
	F_B,
	F_N,
	F_STEALTH,
}				t_flag;

typedef struct	s_arena
{
	unsigned char	map[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				players_count;
	int				cycle_to_die;
	int				cur_cycle;
	int				flags[FLAGS_COUNT];
}				t_arena;

//	main.c
void		print_usage(void);

//	fight.c
void		fight(t_arena *arena);

//	print_map.c
void		print_map(unsigned char *map);

//	load_players.c
void	load_player(char *path, t_arena *arena);

//	load_arena.c
void		load_arena(int argc, char **argv, t_arena *arena);

//	arena_utils.c
void		arena_ini(t_arena *arena);
void		arena_free(t_arena *arena);

//	errors.c
void		error_handle(int error_id, t_arena *arena, char *addition);

//	player_utils.c
void	player_ini(t_player *player);
#endif