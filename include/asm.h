/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:08:27 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/05 12:31:14 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H

# include "general/op.h"
# include "libft.h"
# include <stdio.h> 
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define HEADER		g_asm->matrix[0] 
# define NAME		g_asm->matrix[1] 
# define ZERO1		g_asm->matrix[2] 
# define SIZE		g_asm->matrix[3] 
# define COMMENT	g_asm->matrix[4]
# define ZERO2		g_asm->matrix[5] 
# define CODE 		g_asm->matrix[6]
# define BUFF		3000
# define BUFFER		g_asm->buf
# define INDEX		g_asm->index
/*struct g_asm is for different things:
**	binary_name saves the name of the final binary file
**	in matrix we will have 5 str for final binary code: 
**	matrix[0](HEADER) for magic header; matrix[1](NAME) for name of champion
**	matrix[2](ZERO) for NULL; matrix[3](SIZE) for code size
**	matrix[4](COMMENT) for comment; matrix[5](CODE) for code itself
**  str_count counts str in incomming file (we need it for ex. for error messages)
**	flag_name id used to show, that we found .name and if we will find another 
**		one or no one, we can see it with this flag
**	quotes show if there was an open quote and no closed quote
**	i is an iterator in buf
**	flag_comment id the same as flag_name but for comment
**	index is an index of current command in g_struct array of structs
**	size_of_struct is a size of allocated memory of final struct
**
** The struct g_parse we will use to write info about commands. In every element
** we will write label(if we have it), name of command, its args and str number in 
** file.
*/	

typedef struct s_asm
{
	char		*binary_name;
	char		**matrix;
	char		buf[BUFF];
	int			str_counter;
	int			flag_name;
	int			flag_comment;
	int			i;
	int			index;
	int			size_of_struct;

}				t_asm;

typedef struct s_parse
{
	char		*label;
	char		*command;
	char		**arg;
	int			str_number;
	int			id_in_tab;
	int			byte;
	unsigned char		octet;
}				t_parse;

typedef struct 	s_op
{
	char		name[10];
	int			var_count;
	int			args[3];
	int			id;
	int			cost;
	char		description[100];
	int			kod_tipov_argumenta;
	int			t_dir_size_eq_4;
	//void		(*op_handler)();
	/* data */
}				t_op;

t_asm			*g_asm;
t_parse			*g_struct;
t_op   			g_op_tab[17];

void    usage(void);
void	close_with_error(char *str);
void    lexical_error(void);
void	syntax_error(int flag);
void	syntax_error_instruction(char *instruction, int flag);
void	invalid_error_instruction(char **instruction, int flag);
void	length_error(int nb);
void	del_all_struct(void);
void    init(void);
void	init_struct(void);
void    parse_from_file(int argc, char **argv);
void	skip_comment_and_spaces(void);
void	find_name_comment(void);
void	skip_comment_and_spaces(void);
void	skip_whitespaces(void);
int		find_position_in_str(void);
void    write_labels_commands(void);
int     count_chars(void);
int		check_if_command_exist(char *temp);
int		check_if_label_exist(char *temp);
char	**split(char const *str, char c);
void    check_if_command_has_arg(char **array);
int		check_direct_or_indirect(char *array, int element, int flag);
int		check_register(char *array, int element);
int		find_flag(char *array);
void    realise_algorithm(void);
void	init_matrix_element(char **element, int len);
void 	make_binary(void);
#endif