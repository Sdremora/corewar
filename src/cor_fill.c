#include "corewar.h"

#define MAGIC_SIZE 4
#define NAME_SIZE 128
#define NULL_SIZE 4
#define EXEC_CODE_LEN_SIZE 4
#define COMMENT_SIZE 2048
#define EXEC_CODE_SIZE 100

int	main(void)
{
	char	magic[MAGIC_SIZE];
	char	name[NAME_SIZE];
	char	null1[NULL_SIZE];
	char	exec_code_len[EXEC_CODE_LEN_SIZE];
	char	comment[COMMENT_SIZE];
	char	null2[NULL_SIZE];
	char	exec_code[EXEC_CODE_SIZE];

	ft_bzero(magic, MAGIC_SIZE);
	ft_bzero(name, NAME_SIZE);
	ft_bzero(null1, NULL_SIZE);
	ft_bzero(exec_code_len, EXEC_CODE_LEN_SIZE);
	ft_bzero(comment, COMMENT_SIZE);
	ft_bzero(null2, NULL_SIZE);
	ft_bzero(exec_code, EXEC_CODE_SIZE);
}