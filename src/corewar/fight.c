#include "corewar.h"

void    locate_players(t_arena *arena)
{
    int i;
    int pos;

    pos = 0;
    i = 0;
    while (i < arena->players_count)
    {
        ft_memcpy(arena->map + i * MEM_SIZE / arena->players_count, arena->players[i].code, arena->players[i].code_size);
        i++;
    }


    return ;

}

void	fight(t_arena *arena)
{
    locate_players(arena);

}
