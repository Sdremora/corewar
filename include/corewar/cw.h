
#ifndef CW_H
#define CW_H

#include "general/op.h"

typedef struct	s_player
{
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
	char	*code;
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
	t_player		*players[MAX_PLAYERS];
	int				players_count;
	int				cycle_to_die;
	int				cycle;
}				t_arena;

void	load_players(int argc, char **argv, t_arena *arena);
void	arena_ini(t_arena *arena);
void	fight(t_arena *arena);

#endif