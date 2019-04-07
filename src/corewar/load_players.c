#include "corewar.h"

void	check_magic(int fd, t_arena *arena)
{
	unsigned int magic;

<<<<<<< HEAD
    magic = 0;
    if (read(fd, &magic, 4) != 4)
		error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
	if (magic != 4085508608)
=======
	magic = 0;
	if (read(fd, &magic, 4) != 4 || magic != 4085508608)
>>>>>>> c42174362bf1cb915edd45fdaca9950f975ecf30
		error_handle(E_INV_CHAMP, arena, "bad magic");
}

void	check_null(int fd, t_arena *arena)
{
<<<<<<< HEAD
    unsigned int nulls;

    nulls = 0;
    if (read (fd, &nulls, 4) != 4)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
	if (nulls != 0)
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
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
    *p = swap_int_bytes(size);
    return ;
}

void	read_comment(int fd, t_player *player, t_arena *arena)
{
    if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
}

void    read_code(int fd, int size, char *code, t_arena *arena)
{
	char	temp[10];
	int		len;

	len = read(fd, code, COMMENT_LENGTH);
	if (len < 0)
		error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
    if (len != size)
        error_handle(E_INV_CHAMP, arena, "program size is not equal to the specified value");
	if (read(fd, code, 10) > 0 || len > CHAMP_MAX_SIZE)
		error_handle(E_INV_CHAMP, arena, "the program code of the player is too long");
    return ;
=======
	unsigned int nulls;

	nulls = 0;
	if (read(fd, &nulls, 4) != 4 || nulls != 0)
		error_handle(E_INV_CHAMP, arena, "zero section is not empty");
>>>>>>> c42174362bf1cb915edd45fdaca9950f975ecf30
}

void	load_player(char *path, t_arena *arena)
{
	t_player	*player;
	int			fd;
	int			id;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handle(E_INV_PATH, arena, path);
	player = &(arena->players[get_pnb(arena)]);
	player_ini(player, &arena->flags[F_N]);
	check_magic(fd, arena);
	read_name(fd, player, arena);
	check_null(fd, arena);
	read_code_size(fd, &(player->code_size), arena);
	read_comment(fd, player, arena);
	check_null(fd, arena);
	read_code(fd, player->code_size, player->code, arena);
	arena->players_count++;
	close(fd);
}
