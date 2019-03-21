#include "corewar.h"

void	arena_ini(int nb, t_arena *arena)
{
    arena->players_count = nb;
    ft_bzero(arena->map, MEM_SIZE);
    arena->cycle_to_die = CYCLE_TO_DIE;
    arena->cycle = 0;
}