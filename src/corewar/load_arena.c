#include "corewar.h"

int		handle_flag(char *str, int *argc)
{
// Написать обработку флагов и заполнение их значений в массив arena->flags
// Изначально там все значения = -1.
// Если флаг предполагает, что после него идет значение, например (d 100)
// В таком, случае нужно прочитать значение и увеличить argc на 1
// Если вместо цифр, там оказалась ерунда -> присвоить флагу дефолтное значение и всеравно увеличить argc на 1

//Если функция вернет 0 -> стало быть это не флаг и дальше строка будет обработана, как путь к файлу.
	return (0);
}

void	load_arena(int argc, char **argv, t_arena *arena)
{
	int i;

	arena_ini(arena);
	i = 1;
	while (i < argc)
	{
		if (!handle_flag(argv[i], &argc))
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
		arena_free(arena);
		print_usage();
	}
}
