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

void     read_code_size(int fd, t_player *player, t_arena *arena)
{
}

void	read_comment(int fd, t_player *player, t_arena *arena)
{
    if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
        error_handle(E_INV_CHAMP, arena, "the program code of the player is too short");
}

int     read_code(int fd, int size, char *code)
{
    return (1);
}

void	load_player(char *path, t_arena *arena)
{
	t_player	player;
    int			fd;

    fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handle(E_INV_PATH, arena, path);
	player = arena->players[arena->players_count];
	player_ini(&player);
    check_magic(fd, arena);
	read_name(fd, &player, arena);
	check_null(fd, arena);

	read_comment(fd, &player, arena);
	arena->players_count++;
	ft_printf("name = %s\n", player.name);
	ft_printf("comment = %s\n", player.comment);
    /*
    read_code_size(fd, &(arena->players[i]->code_size));
    read_comment(fd, arena->players[i]->comment);
    read_nulls(fd);
    read_code(fd, arena->players[i]->code_size, arena->players[i]->code);
    */
    close(fd);

}
