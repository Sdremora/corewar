
#include "corewar.h"

void		introducing(t_arena *arena)
{
	int			i;
	t_player	player;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < arena->players_count)
	{
		player = arena->players[i];
		i++;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i, player.code_size, player.name, player.comment);
	}
}
