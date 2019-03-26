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
	return (-1);
}

int			handle_flag(char **argv, int *pos, t_arena *arena)
{
	int i;

	if ((i = get_num_flag(argv[*pos]) > 0))
	{
		if (i >= F_D)
			{
				*pos += 1;
				arena->flags[i] = get_flag_nb(argv[*pos]);
			}
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
		carriage = carg_new(pos, i + 1, 1);
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

void		load_arena(int argc, char **argv, t_arena *arena)
{
	int i;

	arena_ini(arena);
	i = 1;
	while (i < argc)
	{
		if (!handle_flag(argv, &i, arena))
		{
			if (arena->players_count < MAX_PLAYERS)
				load_player(argv[i], arena);
			else
				error_handle(E_OVER_PLAYERS, arena, NULL);
		}
		i++;
	}
	if (arena->players_count == 0)
	{
		arena_clear(arena);
		print_usage();
	}
	locate_players(arena);
}
