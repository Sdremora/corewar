#include "corewar.h"

void	check_magic(int fd, t_arena *arena)
{
    unsigned int magic;

    magic = 0;
    if (read(fd, &magic, 4) != 4 || magic != 4085508608)
		error_handle(E_INV_CHAMP, arena, "bad magic");
}

void	read_name(int fd, t_player *player, t_arena *arena)
{
    if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
}

void	check_null(int fd, t_arena *arena)
{
    unsigned int nulls;

    nulls = 0;
    if (read (fd, &nulls, 4) != 4 || nulls != 0)
        error_handle(E_INV_CHAMP, arena, "zero section is not empty");
}

int    swap_int_bytes(unsigned int nb)
{
    int res;

    res = nb >> 24;
    res |= (nb >> 8) & 0xff00;
    res |= (nb << 8) & 0xff0000;
    res |= (nb << 24);
    return(res);
}

void     read_code_size(int fd, int *p, t_arena *arena)
{
    int size;

    size = 0;
    if (read (fd, &size, 4) != 4)
        error_handle(E_INV_CHAMP, arena, "invalid size");
    *p = swap_int_bytes(size);
    if (*p > (MEM_SIZE / 6))
        error_handle(E_INV_CHAMP, arena, "invalid size");
    return ;
}

void	read_comment(int fd, t_player *player, t_arena *arena)
{
    if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
}

void    read_code(int fd, int size, char *code, t_arena *arena)
{
    if (read(fd, code, size) != size)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
    return ;
}

void	load_player(char *path, t_arena *arena, int pnb)
{
	t_player	*player;
    int			fd;

    fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handle(E_INV_PATH, arena, path);
	player = &(arena->players[pnb]);
	player_ini(player, pnb);
    check_magic(fd, arena);
	read_name(fd, player, arena);
	check_null(fd, arena);
    read_code_size(fd, &(player->code_size), arena);
	read_comment(fd, player, arena);
    check_null(fd, arena);
    read_code(fd, player->code_size, player->code, arena);
    if (arena->last_live_player < player->id)
        arena->last_live_player = player->id;
	arena->players_count++;
    close(fd);
}
