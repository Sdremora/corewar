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
		carg->mem_pos = looping(carg->mem_pos + 1);
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
		arg = arena->map[looping(carg->mem_pos + 1)];
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

	if (carg->op_id == ZJMP && carg->carry == 1)
		return ;
	i = 0;
	move = 1 + g_op_tab[carg->op_id].kod_tipov_argumenta;
	while (i < 3 && g_op_tab[carg->op_id].args[i])
	{
		move += step_bites(carg->args[i], dir_size);
		i++;
	}
	next_pos = looping(carg->mem_pos + move);
	if (arena->flags[F_V] & 16)
	{
		ft_printf("ADV %d (%06p -> %06p) ", move, carg->mem_pos, next_pos);
		i = 0;
		while (i < move)
		{
			ft_printf("%02x ", arena->map[looping(carg->mem_pos + i)]);
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

void		vis_move_carg(int old, int new, t_arena *arena)
{
	int color;

	if ((color = get_color_pair(old, arena->shift)) > 4 && !nb_carg_pos(arena, old))
	{
		draw_pos(arena, color - 5, old);
	}
	if ((color = get_color_pair(new, arena->shift)) < 5)
	{
		draw_pos(arena, color + 5, new);
	}
}

static void	play_round(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;
	int			cur_pos;

    carg_node = arena->carg_lst;
    while (carg_node)
    {
		carg = (t_carriage *)carg_node->content;
		cur_pos = carg->mem_pos;
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
		if (arena->flags[F_VIS])
			vis_move_carg(looping(cur_pos), looping(carg->mem_pos), arena);
    	carg_node = carg_node->next;
    }
}

void		check_live(t_arena *arena)
{
	t_list		*carg_node;
	t_carriage	*carg;
	t_list		*temp;

	ft_bzero(arena->player_live_in_cp, sizeof(int) * MAX_PLAYERS);
	carg_node = arena->carg_lst;
	while (carg_node)
	{
		carg = (t_carriage *)carg_node->content;
		if (arena->cycle_to_die <= 0 || !carg->live)
		{
			if (arena->flags[F_VIS])
				remove_carg(arena, carg->mem_pos);
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
		if (arena->flags[F_VIS])
			print_nb(arena->cycle_to_die, 11 + 4 * arena->players_count + 6, POS_NB, 10);
	}
	else
		arena->checks++;
	arena->live_call_count = 0;
}

void		draw_map(unsigned char *str, t_point p)
{
	int i;
	int j;
	static char base[17] = "0123456789abcdef";

	color_set(0, NULL);
	i = 0;
	while (i < MEM_SIZE)
	{
		mvaddch(p.y + i / 64, p.x +  3 * (i % 64), base[str[i] / 16 % 16]);
		mvaddch(p.y + i / 64, p.x + 3 * (i % 64) + 1, base[str[i] % 16]);
		i++;
	}
}

void		set_color_pairs(void)
{
	start_color();

	init_pair(0,  COLOR_WHITE, COLOR_BLACK);
	init_pair(1,  COLOR_GREEN, COLOR_BLACK);
	init_pair(2,  COLOR_BLUE, COLOR_BLACK);
	init_pair(3,  COLOR_RED, COLOR_BLACK);
    init_pair(4,  COLOR_CYAN, COLOR_BLACK);

	init_pair(5,  COLOR_BLACK, 8);
	init_pair(6,  COLOR_BLACK, COLOR_GREEN);
	init_pair(7,  COLOR_BLACK, COLOR_BLUE);
	init_pair(8,  COLOR_BLACK, COLOR_RED);
    init_pair(9,  COLOR_BLACK, COLOR_CYAN);

/*
    if (COLORS >= 16) {
        init_pair(10, 15, COLOR_BLACK);
    } else {
        init_pair(10, COLOR_WHITE, COLOR_BLACK);
    }
*/
	init_pair(10,  15, COLOR_BLACK);
}

void		draw_players(t_arena *arena)
{
	int i;
	int pos;
	static char base[17] = "0123456789abcdef";

	i = 0;

	while (i < arena->players_count)
	{
		color_set(i + 1 + 5, NULL);
		pos = i * MEM_SIZE / arena->players_count;
		while (pos < i * MEM_SIZE / arena->players_count + arena->players[i].code_size)
		{
			mvaddch(arena->shift.y + pos / 64, arena->shift.x + 3 * (pos % 64), base[arena->map[pos] / 16 % 16]);
			mvaddch(arena->shift.y + pos / 64, arena->shift.x + 3 * (pos % 64) + 1, base[arena->map[pos] % 16]);
			if (pos == i * MEM_SIZE / arena->players_count)
				color_set(i + 1, NULL);
			pos++;
		}

		i++;
	}

}

void		draw_box(void)
{
	int i;

	i = 0;
	color_set(5, NULL);
	while (i < 250)
	{
		mvaddch(0, i, ' ');
		mvaddch(67, i, ' ');
		i++;
	}
	i = 0;
	while (i < 67)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, 1, ' ');
		mvaddch(i, 197, ' ');
		mvaddch(i, 198, ' ');
		mvaddch(i, 248, ' ');
		mvaddch(i, 249, ' ');
		i++;
	}
}

int		draw_status(t_arena *arena)
{
	int i;

	color_set(10, NULL);
	mvaddstr(2,POS_TEXT,"** PAUSED **");
	mvaddstr(5,POS_TEXT,"Cycles/second limit :");
	mvaddstr(5, POS_NB,"50");
	mvaddstr(7,POS_TEXT,"Cycle :");
	mvaddstr(7, POS_NB,"50");
	mvaddstr(9,POS_TEXT,"Processes :");
	print_nb(arena->max_carg_id, 9, POS_NB, 10);
	i = 0;
	while (i < arena->max_carg_id)
	{
		mvaddstr(11 + 4 * i,POS_TEXT,"Player -1 :");
		mvaddch(11 + 4 * i, 209, '0' + i + 1);
		mvaddstr(11 + 4 * i,213,arena->players[i].name);
		mvaddstr(11 + 4 * i + 1, 203,"Last live :");
		mvaddstr(11 + 4 * i + 1, POS_NB,"0");
		mvaddstr(11 + 4 * i + 2, 203, "Current lives :");
		mvaddstr(11 + 4 * i + 2, POS_NB,"0");
		i++;
	}
	mvaddstr(11 + 4 * i , POS_TEXT , "Live breakdown for current period :");
	mvaddstr(11 + 4 * i + 1 , POS_TEXT,"[--------------------------------------------------]");
	mvaddstr(11 + 4 * i + 3 , POS_TEXT , "Live breakdown for last period :");
	mvaddstr(11 + 4 * i + 6 , POS_TEXT , "Cycle to die :");
	print_nb(arena->cycle_to_die, 11 + 4 * i + 6, POS_NB, 10);
	mvaddstr(11 + 4 * i + 8 , POS_TEXT , "Number checks :");
	print_nb(arena->checks, 11 + 4 * i + 8, POS_NB, 10);
	return (i);
}

void		fight(t_arena *arena)
{
	introducing(arena);
	char temp;
	int speed;
	int pause;

	if (arena->flags[F_VIS] == 1)
	{
		int x = 4;
		int y = 2;

		arena->shift = ft_pnt(x, y);
		initscr();
		assume_default_colors(8, COLOR_BLACK);
		noecho();
		set_color_pairs();
		draw_map(arena->map, arena->shift);
		draw_box();
		draw_status(arena);
		draw_players(arena);
		curs_set(0);
		refresh();
		speed = 20000;
		pause = 1;
	}
    while (arena->carg_lst)
    {
			if (arena->flags[F_VIS])
			{
				print_nb(arena->cur_cycle, 7, POS_NB, 10);
				refresh();
				vis_pause(&pause, &speed);
				refresh();
				usleep(speed);
			}
			if (arena->cur_cycle == arena->flags[F_D])
				return print_map(arena->map, 64);
			if (arena->cur_cycle == arena->flags[F_S] && arena->flags[F_S] > 0)
			{	
				print_map(arena->map, 64);
				read(0, 0, 1);
				arena->flags[F_S] += arena->flags[F_STEALTH];
			}
			arena->cur_cycle++;
			if (arena->flags[F_V] & 2)
				ft_printf("It is now cycle %d\n", arena->cur_cycle);
			arena->cycle_past_check++;
			play_round(arena);
			if (arena->cycle_past_check == arena->cycle_to_die || arena->cycle_to_die <= 0)
			{
				arena->cycle_past_check -= arena->cycle_to_die;
				check_live(arena);
				check_cycle_to_die(arena);
			}

    }
}
