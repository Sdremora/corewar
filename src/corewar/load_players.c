#include "corewar.h"

int     check_magic(int fd)
{
    unsigned int magic;

    magic = 0;
    if (read(fd, &magic, 4) == 4)
        return (magic == 4085508608);
    return (0);
}

int     read_name(int fd, char *name)
{
    char buf[2000];

    if (read(fd, buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
        return (0);
    buf[PROG_NAME_LENGTH] = 0;
    ft_strcpy(name,buf);///?????????????????????????
    return (1);
}

int     read_nulls(int fd)
{
    unsigned int nulls;

    nulls = 0;
    if (read (fd, &nulls, 4) != 4 || nulls != 0)
        return(0);
    return (1);
}

int     read_code_size(int fd, int *p)
{
    return (1);
}

int     read_comment(int fd, char *str)
{
    return (1);
}

int     read_code(int fd, int size, char *code)
{
    return (1);
}

void	load_players(int argc, char **argv, t_arena *arena)
{
    int i;
    int fd;

    i = 0;
    while (i < argc)
    {
        fd = open(argv[i], O_RDONLY);
        check_magic(fd);
        read_name(fd, arena->players[i].name);
        printf("%s\n", arena->players[i].name);
        read_nulls(fd);
        /*
        read_code_size(fd, &(arena->players[i]->code_size));
        read_comment(fd, arena->players[i]->comment);
        read_nulls(fd);
        read_code(fd, arena->players[i]->code_size, arena->players[i]->code);
        */
        close(fd);
        i++;
        
    }

}
