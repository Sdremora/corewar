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
	if (ft_strequ(str, "-dump"))
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
				arena->flags[i] = get_flag_nb(argv[*pos]);
			else
				print_usage();
				/*
			if (i == F_N && (arena->flags[i] == 0 || arena->flags[i] > MAX_PLAYERS))
				print_usage();
			else
				arena->flags[i] -= 1;
				*/
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
		pos = arena->players[i].id * MEM_SIZE / arena->players_count;
        ft_memcpy(arena->map + pos, arena->players[i].code, arena->players[i].code_size);
		carriage = carg_new(pos, arena->players[i].id + 1, 1);
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

int			get_pnb(t_arena *arena)
{
	int i;
	int res;
	static int nb = MAX_PLAYERS;

	if ((i = arena->flags[F_N]) != -1)
	{
		if (i < MAX_PLAYERS)
		{
			res = arena->flags[F_N];
			arena->flags[F_N] = -1;
			return (res);
		}
		else
			error_handle(E_PLAYER_NUMBER, arena, NULL);
	}
//	nb++;
//	return (nb - 1);
	return (nb++);
	/*
	else
	{
		i = 0;
		while (i < MAX_PLAYERS && arena->players[i].id != -1)
			i++;
	}
	if (i == MAX_PLAYERS)
		error_handle(E_OVER_PLAYERS, arena, NULL);
	return (i);
	*/
}



int		find_min_id(t_arena *arena)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 1;
	while (i < arena->players_count)
	{
		j = 0;
		flag = 1;
		while (j < arena->players_count)
		{
			if (arena->players[j].id == i)
			{
				flag = 0;
				break ;
			}
			j++;
		}
		if (flag)
			return (i);
		i++;
	}
	return (-42);
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
	if (find_min_id(arena) >= 0)
		return (0);
	return (1);
}

void		relocate_players(t_arena *arena)
{
	int i;
	int j;

	i = 0;
	while (i < arena->players_count)
	{
		if (arena->players[i].id >= MAX_PLAYERS)
		{
			arena->players[i].id = find_min_id(arena);
		}
		i++;
	}
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
	printf("---->ids %d %d %d     ", arena->players[0].id,arena->players[1].id,arena->players[2].id);
	relocate_players(arena);
	printf("---->ids %d %d %d", arena->players[0].id,arena->players[1].id,arena->players[2].id);
	printf("{%d}{%d}", find_min_id(arena), !check_players(arena));

	if (arena->players_count == 0 || !check_players(arena))
	{
		arena_clear(arena);
		error_handle(E_PLAYER_NUMBER, arena, NULL);
//		print_usage();
	}
	locate_players(arena);
}
