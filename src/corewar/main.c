#include "corewar.h"

int	main(int argc, char **argv)
{
	t_arena		arena;

	load_players(argc, argv, &arena);
	arena_ini(&arena);
	fight(&arena);
	return (0);
}
