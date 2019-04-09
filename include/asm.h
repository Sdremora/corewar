/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:08:27 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 17:40:07 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "general/op.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

# define HEADER		g_asm->matrix[0]
# define NAME		g_asm->matrix[1]
# define ZERO1		g_asm->matrix[2]
# define SIZE		g_asm->matrix[3]
# define COMMENT	g_asm->matrix[4]
# define ZERO2		g_asm->matrix[5]
# define CODE 		g_asm->matrix[6]
# define BUFF		50000
# define BUFFER		g_asm->buf
# define INDEX		g_asm->index

/*
**	struct g_asm is for different things:
**	binary_name saves the name of the final binary file
**	in matrix we will have 5 str for final binary code:
**	matrix[0](HEADER) for magic header; matrix[1](NAME) for name of champion
**	matrix[2](ZERO) for NULL; matrix[3](SIZE) for code size
**	matrix[4](COMMENT) for comment; matrix[5](CODE) for code itself
**  str_count counts str in incomming file
**	(we need it for ex. for error messages)
**	flag_name id used to show, that we found .name and if we will find another
**		one or no one, we can see it with this flag
**	quotes show if there was an open quote and no closed quote
**	i is an iterator in buf
**	flag_comment id the same as flag_name but for comment
**	index is an index of current command in g_struct array of structs
**	size_of_struct is a size of allocated memory of final struct
**
**	The struct g_parse we will use to write info about commands.
**	In every element we will write label(if we have it), name of command,
**	its args and str number in file.
*/

typedef struct		s_asm
{
	char			*binary_name;
	char			**matrix;
	unsigned char	buf[BUFF];
	int				str_counter;
	int				flag_name;
	int				flag_comment;
	int				i;
	int				index;
	int				shift;
	int				size_of_struct;

}					t_asm;

typedef struct		s_parse
{
	char			*label;
	char			*command;
	char			**arg;
	int				str_number;
	int				id_in_tab;
	int				byte;
	unsigned char	octet;
}					t_parse;

typedef struct		s_op
{
	char			name[10];
	int				var_count;
	int				args[3];
	int				id;
	int				cost;
	char			description[100];
	int				kod_tipov_argumenta;
	int				t_dir_size_eq_4;
}					t_op;

t_asm				*g_asm;
t_parse				**g_struct;
t_op				g_op_tab[17];

void				usage(void);
void				close_with_error(char *str);
void				lexical_error(void);
void				syntax_error(int flag);
void				syntax_error_instruction(char *instruction, int flag);
void				invalid_error_instruction(char **instruction, int flag);
void				length_error(int nb);
void				error_no_label(char *label, int index);
void				del_all_struct(void);
void				init(void);
void				init_struct(void);
void				parse_from_file(int argc, char **argv);
void				skip_comment_and_spaces(void);
void				find_name_comment(void);
void				skip_comment_and_spaces(void);
void				skip_whitespaces(void);
int					find_position_in_str(void);
void				write_labels_commands(void);
int					count_chars(void);
int					check_if_command_exist(char *temp);
int					check_if_label_exist(char *temp);
char				**split(char const *str);
void				check_if_command_has_arg(char **array);
int					check_direct_or_indirect(char *array, int element,
									int flag);
int					check_register(char *array, int element);
void				check_labels_validity(char **temp);
int					find_flag(char *array);
int					find_id_in_tab(void);
void				realise_algorithm(void);
void				init_matrix_element(char **element, int len);
int					count_args_size(void);
void				check_invalid_args_end_of_file(char **temp);
void				check_invalid_number_of_args(char ***array,
									int i, int flag);
void				handle_arg(char *arg, int i, int *k, char *pre_matrix);
int					find_right_label(int i, char *label);
void				make_binary(void);
void				print_hexdump(void);
void				print_noll(int nb);
int					find_position_in_str(void);
int					find_position_in_str_for_instruction(char *instruction);
int					find_label_index(char *label, int *flag);
void				skip_whitespaces_com(void);
int					count_all_str(void);
#endif
