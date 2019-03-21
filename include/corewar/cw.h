
#ifndef CW_H
#define CW_H

#define REVERSE_MAGIC 4085508608

#include "general/op.h"

typedef struct	s_player
{
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH];
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

typedef struct	s_arena
{
	unsigned char	map[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				players_count;
	int				cycle_to_die;
	int				cycle;
}				t_arena;

void	load_players(int argc, char **argv, t_arena *arena);
void	arena_ini(int nb, t_arena *arena);
void	fight(t_arena *arena);
void	print_map(unsigned char *map);

#endif