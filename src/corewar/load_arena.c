#include "corewar.h"

int		get_flag_nb(char *str)
{
	long long int	nb;

	nb = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			print_usage();
		str++;
	}
	if (*str == 0)
		print_usage();
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - '0';
		if (nb > 2147483647)
			print_usage();
		str++;
	}
	if (*str != 0)
		print_usage();
	return (nb);
}

int			get_num_flag(char *str)
{
	if (ft_strequ(str, "-a"))
		return (F_A);
	if (ft_strequ(str, "-dump") || ft_strequ(str, "-d"))
		return (F_D);
	if (ft_strequ(str, "-s"))
		return (F_S);
	if (ft_strequ(str, "-v"))
		return (F_V);
	if (ft_strequ(str, "-b"))
		return (F_B);
	if (ft_strequ(str, "-n"))
		return (F_N);
	if (ft_strequ(str, "--stealth"))
		return (F_STEALTH);
	if (ft_strequ(str, "-vis"))
		return (F_VIS);
	return (-1);
}

int			handle_flag(char **argv, int *pos, int argc, t_arena *arena)
{
	int i;

	if ((i = get_num_flag(argv[*pos])) > 0)
	{
		if (i >= F_D) //флаги с числами
		{
			*pos += 1;
			if (*pos < argc)
			{
				arena->flags[i] = get_flag_nb(argv[*pos]);
			}
			else
				print_usage();
		}
		else
			arena->flags[i] = 1;
		return (1);
	}
// Написать обработку флагов и заполнение их значений в массив arena->flags
// Изначально там все значения = -1.
// Если флаг предполагает, что после него идет значение, например (d 100)
// В таком, случае нужно прочитать значение и увеличить argc на 1
// Если вместо цифр, там оказалась ерунда -> присвоить флагу дефолтное значение и всеравно увеличить argc на 1

//Если функция вернет 0 -> стало быть это не флаг и дальше строка будет обработана, как путь к файлу.
	return (0);
}

static void	locate_players(t_arena *arena)
{
    int 		i;
    int 		pos;
	t_carriage	*carriage;
	t_list		*node;

    i = 0;
    while (i < arena->players_count)
    {
		pos = i * MEM_SIZE / arena->players_count;
        ft_memcpy(arena->map + pos, arena->players[i].code, arena->players[i].code_size);
		arena->max_carg_id++;
		carriage = carg_new(pos, i + 1, 0, arena->max_carg_id);
		if (carriage == NULL)
			error_handle(E_NO_MEM, arena, NULL);
		node = ft_lstput(carriage, sizeof(t_carriage));
		if (node == NULL)
			error_handle(E_NO_MEM, arena, NULL);
		ft_lstadd(&arena->carg_lst, node);
        i++;
    }
    return ;
}

void		add_swap_players(t_arena *arena, int pos)
{
	int			i;
	t_player	temp;

	i = 0;
	while (i < pos && arena->players[i].id > arena->players[pos].id)
		i++;
	if (i == pos)
		return ;
	else
	{
		temp = arena->players[pos];
		arena->players[pos] = arena->players[i];
		arena->players[i] = temp;
	}
	add_swap_players(arena, i);
}

void		swap_players(t_arena *arena, int pos)
{
	int			i;
	t_player	temp;

	i = 0;
	while (i < MAX_PLAYERS && arena->players[i].id != -1)
		i++;
	if (i == MAX_PLAYERS)
		error_handle(E_PLAYER_NUMBER, arena, NULL);
	temp = arena->players[pos];
	arena->players[pos] = arena->players[i];
	arena->players[i] = temp;
	add_swap_players(arena, i);
}

int			get_pnb(t_arena *arena)
{
	int i;
	int res;
	static int nb = MAX_PLAYERS;

	if ((i = arena->flags[F_N]) != -1)
	{
		i--;
		if (i >= 0 && i < MAX_PLAYERS && arena->players[i].id < 0)
		{
			res = arena->flags[F_N];
			if (arena->players[i].id < -1)
				swap_players(arena, i);
			return (i);
		}
		else
			error_handle(E_PLAYER_NUMBER, arena, NULL);
	}
	i = 0;
	while (arena->players[i].id != -1)
		i++;
	return (i);
}




int			check_players(t_arena *arena)
{
	int i;

	i = 0;
	while (i < arena->players_count)
	{
		if (arena->players[i].id == -1 || arena->players[i].id >= arena->players_count)
			return (0);
		i++;
	}
	return (1);
}


void		load_arena(int argc, char **argv, t_arena *arena)
{
	int i;

	arena_ini(arena);
	i = 1;
	while (i < argc)
	{
		if (!handle_flag(argv, &i, argc, arena))
		{
			if (arena->players_count < MAX_PLAYERS)
				load_player(argv[i], arena);
			else
				error_handle(E_OVER_PLAYERS, arena, NULL);
		}
		i++;
	}
	if (arena->players_count == 0 || !check_players(arena))
	{
		arena_clear(arena);
		error_handle(E_PLAYER_NUMBER, arena, NULL);
	}
	arena->last_live_player = arena->players_count - 1;
	locate_players(arena);
}
