#include "corewar.h"

void	print_usage(void)
{
	ft_printf("Usage: Bongiorno!\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_arena		arena;

	if (argc == 1)
		print_usage();
	load_arena(argc, argv, &arena);
	fight(&arena);
	ft_printf("Contestant %d, \"%s\", has won !\n", arena.last_live_player + 1, arena.players[arena.last_live_player].name);
	return (0);
}
