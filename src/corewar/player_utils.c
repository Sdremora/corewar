#include "corewar.h"

void	player_ini(t_player *player, int *fn)
{
	static int i = 0;

	ft_bzero(player->name, PROG_NAME_LENGTH + 1);
	ft_bzero(player->name, COMMENT_LENGTH + 1);
	ft_bzero(player->name, CHAMP_MAX_SIZE);
	if (*fn >= 0)
	{
		player->id = *fn - 1;
		*fn = -1;
	}
	else
	{
		player->id = -2 - i;
		i++;
	}
}
