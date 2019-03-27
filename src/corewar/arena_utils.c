#include "corewar.h"

void	arena_ini(t_arena *arena)
{
	int i;

	ft_bzero(arena->map, MEM_SIZE);
	arena->players_count = 0;
    arena->cycle_to_die = CYCLE_TO_DIE;
    arena->cur_cycle = 0;
	arena->cycle_past_check = 0;
	arena->checks = 0;
	i = 0;
	while (i < FLAGS_COUNT)
		arena->flags[i++] = -1;
	arena->carg_lst = NULL;
	arena->last_live_player = 0;
	arena->live_call_count = 0;
}

//Дописать очистку арены.
//Оставить проверку на ноль.
//Арена может приходить на очистку в не полностью загруженном состояние (при ошибках в её загрузке), учесть что могут быть нули.
void	arena_clear(t_arena *arena)
{
	t_list	*temp;

	if (!arena)
		return ;
	while (arena->carg_lst)
	{
		temp = arena->carg_lst->next;
		free(arena->carg_lst);
		arena->carg_lst = temp;
	}
}

void    arena_print(t_arena *arena)
{
    t_list *lst;

    lst = arena->carg_lst;
    while (lst)
    {
        ft_printf("pos %d owner %d\n", ((t_carriage*)lst->content)->mem_pos, ((t_carriage*)lst->content)->owner);
        lst = lst->next;
    }
}
