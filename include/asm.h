/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:08:27 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 15:36:43 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H

#include "general/op.h"
#include "libft.h"
#include <stdio.h>

# define HEADER		g_asm->matrix[0] 
# define NAME		g_asm->matrix[1] 
# define ZERO		g_asm->matrix[2] 
# define SIZE		g_asm->matrix[3] 
# define COMMENT	g_asm->matrix[4] 
# define CODE 		g_asm->matrix[5]
# define BUFF		5000

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
*/	

typedef struct s_asm
{
	char		*binary_name;
	char		**matrix;
	int			str_counter;
	int			flag_name;
	int			flag_comment;
	int			quotes;
	int			i;

}				t_asm;


t_asm			*g_asm;

void    usage(void);
void	close_with_error(char *str);
void	del_all_struct(void);
void    init(void);
// void	find_position_error_lex_name_comment(char **line);
void    parse_from_file(int argc, char **argv);
void	skip_comment_and_spaces(char *buf);
void		find_name_comment(char	*buf);
void	skip_comment_and_spaces(char *buf);
void	skip_whitespaces(char *buf);
// int		find_name(char **line);
// int		find_comment(char **line);

#endif