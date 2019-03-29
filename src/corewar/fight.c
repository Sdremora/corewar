#include "corewar.h"

int			step_bites(int arg, int dir_size) //счетчик отступов для аргументов
{
	if (arg == T_REG)
		return (1);
	if (arg == T_DIR)
		return (dir_size);
	if (arg == T_IND)
		return (2);
	if (arg == 0)
		return (0);
	return (-42);
}

static void	operations_handle(t_carriage *carg, t_arena *arena)
{
	unsigned char	oper;

	oper = arena->map[carg->mem_pos] - 1;
	if (oper >= LIVE && oper <= AFF)
	{
			carg->pause_count = g_op_tab[oper].cost;
			carg->op_id = oper;
	}
	else
		carg->mem_pos = get_pos(carg->mem_pos + 1);
}

int			convert_args(unsigned char arg)
{
	if (arg == REG_CODE)
		return (T_REG);
	if (arg == DIR_CODE)
		return (T_DIR);
	if (arg == IND_CODE)
		return (T_IND);
	return (0);
}

void		load_args(t_carriage *carg, t_arena *arena)
{
	unsigned char	arg;
	unsigned char	temp;
	int				i;

	if (g_op_tab[carg->op_id].kod_tipov_argumenta)
	{
		i = 0;
		arg = arena->map[get_pos(carg->mem_pos + 1)];
		while (i < 3 && g_op_tab[carg->op_id].args[i])
		{
			carg->args[i] = convert_args(arg >> (6 - 2 * i) & 3);
			i++;
		}
	}
	else
		carg->args[0] = T_DIR;
}

int			check_code_args(int args[3], unsigned char op_id)
{
	int i;

	i = 0;
	while (i < 3 && g_op_tab[op_id].args[i])
	{
		if (!(args[i] & g_op_tab[op_id].args[i]))
			return (0);
		i++;
	}
	return (1);
}

void		move_carriage(t_arena *arena, t_carriage *carg, int dir_size)
{
	int move;
	int	next_pos;
	int i;

	if (carg->op_id == ZJMP)
		return ;
	i = 0;
	move = 1 + g_op_tab[carg->op_id].kod_tipov_argumenta;
	while (i < 3 && g_op_tab[carg->op_id].args[i])
	{
		move += step_bites(carg->args[i], dir_size);
		i++;
	}
	next_pos = get_pos(carg->mem_pos + move);
	if (arena->flags[F_V] & 16)
	{
		ft_printf("ADV %d (%06p -> %06p) ", move, carg->mem_pos, next_pos);
		i = 0;
		while (i < move)
		{
			ft_printf("%02x ", arena->map[get_pos(carg->mem_pos + i)]);
			// ft_putchar(' ');
			// print_octet(arena->map[get_pos(carg->mem_pos + i)]);
			i++;
		}
		ft_putchar('\n');
	}
	carg->mem_pos = next_pos;
}

void		clean_carg_op(t_carriage *carg)
{
	carg->op_id = -1;
	ft_bzero(carg->args, sizeof(int) * 3);
}

static void	play_round(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;

    carg_node = arena->carg_lst;
    while (carg_node)
    {
		carg = (t_carriage *)carg_node->content;
		if (carg->op_id == -1)
		{
			operations_handle(carg, arena);
		}
		if (carg->pause_count > 0)
			carg->pause_count--;
		if (carg->op_id > -1 && carg->pause_count == 0)
		{
			load_args(carg, arena);
			if (!g_op_tab[carg->op_id].kod_tipov_argumenta
			|| check_code_args(carg->args, carg->op_id))
			{
				g_op_tab[carg->op_id].op_handler(carg, arena);
			}
			move_carriage(arena, carg, g_op_tab[carg->op_id].dir_size);
			clean_carg_op(carg);
		}
    	carg_node = carg_node->next;
    }
}

void		check_live(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;
	t_list		*temp;

	carg_node = arena->carg_lst;
	while (carg_node)
	{
		carg = (t_carriage *)carg_node->content;
		if (arena->cycle_to_die <= 0 || !carg->live)
		//if (arena->cycle_to_die <= 0 || arena->cur_cycle - carg->last_live_cycle > arena->cycle_to_die)
		{
			temp = carg_node->next;
			if (arena->flags[F_V] & 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", carg->carg_id, arena->cur_cycle - carg->last_live_cycle, arena->cycle_to_die);
			arena->carg_lst = ft_lstdelsave(arena->carg_lst, carg_node, ft_lstdelfun);
			carg_node = temp;
			continue ;
		}
		else
			carg->live = 0;
		carg_node = carg_node->next;
	}
}

void		check_cycle_to_die(t_arena *arena)
{
	if (arena->live_call_count >= NBR_LIVE || arena->checks >= MAX_CHECKS)
	{
		arena->cycle_to_die -= CYCLE_DELTA;
		if (arena->flags[F_V] & 2)
			ft_printf("Cycle to die is now %d\n", arena->cycle_to_die);
		arena->checks = 1;
	}
	else
		arena->checks++;
	arena->live_call_count = 0;
}

void		fight(t_arena *arena)
{
	introducing(arena);
    while (arena->carg_lst)
    {
			if (arena->cur_cycle == arena->flags[F_D])
				return print_map(arena->map, 64);
			arena->cur_cycle++;
			if (arena->flags[F_V] & 2)
				ft_printf("It is now cycle %d\n", arena->cur_cycle);
				//ft_printf("{yellow}It is now cycle %d{def}\n", arena->cur_cycle);
			arena->cycle_past_check++;
			if (arena->cycle_past_check == arena->cycle_to_die || arena->cycle_to_die <= 0)
			{
				arena->cycle_past_check -= arena->cycle_to_die;
				check_live(arena);
				check_cycle_to_die(arena);
			}
			play_round(arena);
    }
	ft_printf("циклов -> %d\n", arena->cur_cycle);
}
