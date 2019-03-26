#include "corewar.h"

t_carriage *carg_new(int pos, int owner, int cycle)
{
    t_carriage *res;

    res = (t_carriage*)malloc(sizeof(t_carriage));
    res->owner = owner;
    res->mem_pos = pos;
    res->pause_count = 0;
    ft_bzero(res->reg, (REG_NUMBER) * sizeof(int));
    res->op_id = -1;
    res->last_live_cycle = cycle;
    res->live = 1;
    return (res);
}
