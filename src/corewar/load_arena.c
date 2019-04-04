#include "corewar.h"

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
	arena->flags[F_STEALTH] = arena->flags[F_S];
	locate_players(arena);
}
