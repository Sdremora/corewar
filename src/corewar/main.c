#include "corewar.h"

void	print_usage(void)
{
	ft_printf("./corewar [-d N -s N -v N | -vis] [-a] -n N <champion1.cor> <...>\n");
	ft_printf("  %-16s: Prints output from \"aff\" (Default is to hide it)\n", "-a");
	ft_printf("#### TEXT OUTPUT MODE ##########################################################\n");
	ft_printf("  %-16s: Dumps memory after N cycles then exits\n", "-d (or -dump) N");
	ft_printf("  %-16s: Verbosity levels, can be added together to enable several\n", "-v N");
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
