#include "corewar.h"

void	player_ini(t_player *player, int player_id)
{
	ft_bzero(player->name, PROG_NAME_LENGTH + 1);
	ft_bzero(player->name, COMMENT_LENGTH + 1);
	ft_bzero(player->name, CHAMP_MAX_SIZE);
	player->id = player_id;
}
