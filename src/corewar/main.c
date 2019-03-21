#include "corewar.h"

int	main(int argc, char **argv)
{
	t_arena		arena;

	arena_ini(--argc, &arena);
	load_players(argc, ++argv, &arena);
	fight(&arena);
//	print_map(arena.map);
	return (0);
}
