#include "corewar.h"

void	arena_ini(t_arena *arena)
{
	int i;

	ft_bzero(arena->map, MEM_SIZE);
	arena->players_count = 0;
    arena->cycle_to_die = CYCLE_TO_DIE;
    arena->cur_cycle = 0;
	i = 0;
	while (i < FLAGS_COUNT)
		arena->flags[i++] = -1;
}

//Дописать очистку арены.
//Оставить проверку на ноль.
//Арена может приходить на очистку в не полностью загруженном состояние (при ошибках в её загрузке), учесть что могут быть нули.
void	arena_free(t_arena *arena)
{
	if (!arena)
		return ;
}
