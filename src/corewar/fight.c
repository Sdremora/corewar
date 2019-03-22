#include "corewar.h"

t_carriage *carg_new(int pos, int owner)
{
    t_carriage *res;

    res = (t_carriage*)malloc(sizeof(t_carriage));
    res->owner = owner;
    res->mem_pos = pos;
    res->pause_count = 0;
    ft_bzero(res->reg, (REG_NUMBER) * sizeof(int));
    return (res);    
}

void    locate_players(t_arena *arena)
{
    int i;
    int pos;
    t_list  *cargs;

    i = 0;
    cargs = 0;
    while (i < arena->players_count)
    {
        ft_memcpy(arena->map + i * MEM_SIZE / arena->players_count, arena->players[i].code, arena->players[i].code_size);
        ft_lstadd(&cargs, ft_lstput(carg_new(i * MEM_SIZE / arena->players_count, i + 1), sizeof(t_carriage)));
        i++;
    }
    arena->carg = cargs;
    return ;
}

void    print_arena(t_arena *arena)
{
    t_list *lst;

    lst = arena->carg;
    while (lst)
    {
        ft_printf("pos %d owner %d\n", ((t_carriage*)lst->content)->mem_pos, ((t_carriage*)lst->content)->owner);
        lst = lst->next;
    }
}

void    move_carg(t_carriage *carg, t_list *all_carges, int *carge_count)
{
    *carge_count -= 1;
}

void	fight(t_arena *arena)
{
    int     carg_count;
    t_list  *carg;

    locate_players(arena);
    carg_count = ft_lstlen(arena->carg);
    while (carg_count)
    {
        arena->cur_cycle++;
        carg = arena->carg;
        while (carg)
        {
            move_carg((t_carriage*)carg->content, arena->carg, &carg_count);
            carg = carg->next;
        }
    }
    print_arena(arena);
}
