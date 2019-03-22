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
	print_map(arena.map);
	return (0);
}
