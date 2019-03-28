#include "corewar.h"

t_carriage *carg_new(int pos, int owner, int cycle, int carg_id)
{
    t_carriage *res;

    res = (t_carriage*)malloc(sizeof(t_carriage));
    res->owner = owner;
    res->mem_pos = pos;
    res->pause_count = 0;
    ft_bzero(res->reg, (REG_NUMBER) * sizeof(int));
	res->reg[0] = owner * -1;
    res->op_id = -1;
    res->last_live_cycle = cycle;
    res->live = 0;
	res->carg_id = carg_id;
    return (res);
}

t_carriage	*carriage_copy(t_carriage *carg, int new_id)
{
	t_carriage *new_carg;

	new_carg = carg_new(carg->mem_pos, carg->owner, carg->last_live_cycle, new_id);
	if (new_carg == NULL)
		return (NULL);
	ft_memcpy(new_carg->reg, carg->reg, REG_NUMBER * sizeof(int));
	return (new_carg);
}

void	carriage_free(t_carriage **carg)
{
	free(*carg);
	*carg = NULL;
}
