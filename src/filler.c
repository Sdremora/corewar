#include "corewar.h"

#define MAGIC_SIZE 4
#define NAME_SIZE 128
#define NULL_SIZE 4
#define EXEC_CODE_LEN_SIZE 4
#define COMMENT_SIZE 2048
#define EXEC_CODE_SIZE 100

void	print_usage(void)
{
	ft_printf("./filler <file_with_src> <file_out>\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	char	magic[MAGIC_SIZE];
	char	name[NAME_SIZE];
	char	null1[NULL_SIZE];
	char	exec_code_len[EXEC_CODE_LEN_SIZE];
	char	comment[COMMENT_SIZE];
	char	null2[NULL_SIZE];
	char	exec_code[EXEC_CODE_SIZE];
	int		fd_in;
	int		fd_out;

	if (argc != 3)
		print_usage();
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[2], O_RDONLY);
	if ((fd_in = open(argv[1], O_RDONLY)) < 0 ||
		(fd_out = open(argv[2], O_RDWR | O_CREAT, 0644) < 0))
	{
		ft_printf("error\n");
		return (-1);
	}
	ft_bzero(magic, MAGIC_SIZE);
	ft_bzero(name, NAME_SIZE);
	ft_bzero(null1, NULL_SIZE);
	ft_bzero(exec_code_len, EXEC_CODE_LEN_SIZE);
	ft_bzero(comment, COMMENT_SIZE);
	ft_bzero(null2, NULL_SIZE);
	ft_bzero(exec_code, EXEC_CODE_SIZE);
	magic[0] = 1;
	magic[1] = 2;
	magic[2] = 3;
	magic[3] = 4;
	ft_strcat(name, "champ");
	ft_strcat(comment, "hi-ho");
	exec_code_len[0] = 9;
	ft_strcat(exec_code, "0bxDxD");
	write(fd_out, magic, MAGIC_SIZE);
	write(fd_out, name, NAME_SIZE);
	write(fd_out, null1, NULL_SIZE);
	write(fd_out, exec_code_len, EXEC_CODE_LEN_SIZE);
	write(fd_out, comment, COMMENT_SIZE);
	write(fd_out, null2, NULL_SIZE);
	write(fd_out, exec_code, EXEC_CODE_SIZE);
	close(fd_out);
	close(fd_in);
}
