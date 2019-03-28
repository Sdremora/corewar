/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:58:45 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/28 14:48:29 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    write_name_comment_to_matrix(char i, char *matrix_element, int j)
{
	char	*temp;

	temp = ft_itoa_base_unsgn(i, 16, 1);
	if (i < 16 && i != 34)
		matrix_element[j + 1] = temp[0];
	else if (i >= 16)
	{
		matrix_element[j] = temp[0];
		matrix_element[j + 1] = temp[1];
	}
	ft_strdel(&temp);
}
 

int		going_throw_two_quotes(int	limit, char *matrix_element)
{
	int		counter;
	skip_whitespaces();
	if (g_asm->buf[g_asm->i] == '\n' || g_asm->buf[g_asm->i] == '#')
		syntax_error(5);
	if (g_asm->buf[g_asm->i] != '"')
		lexical_error();
	g_asm->i++;
	counter = 0;
	while (g_asm->buf[g_asm->i] != '"' && g_asm->buf[g_asm->i] != '\0')
	{
		counter += 2;
		if (g_asm->buf[g_asm->i] == '\n')
			g_asm->str_counter++;
		if (counter > limit)
			return (-1);
		write_name_comment_to_matrix(g_asm->buf[g_asm->i], matrix_element, counter - 2);
		g_asm->i++;
	}
		return (1);
}

void		find_name_comment(void)
{
	if (ft_strnequ(".name", &g_asm->buf[g_asm->i], 5) != 0)
	{
		if (g_asm->flag_name == -1)
			g_asm->flag_name = 1;
		else if (g_asm->flag_name == 1)
			syntax_error(2);
		g_asm->i += 5;
		if (going_throw_two_quotes(PROG_NAME_LENGTH, NAME) == -1)
		{
			g_asm->flag_comment = 1;
			g_asm->flag_name = 0;
		}
	}
	else if (ft_strnequ(".comment", &g_asm->buf[g_asm->i], 8) != 0)
	{
		if (g_asm->flag_comment == -1)
			g_asm->flag_comment = 1;
		else if (g_asm->flag_comment == 1)
			syntax_error(1);
		g_asm->i += 8;
		if (going_throw_two_quotes(COMMENT_LENGTH, COMMENT) == -1)
		{
			g_asm->flag_name = 1;
			g_asm->flag_comment = 0;
		}	
	}
	else if (g_asm->buf[g_asm->i] == '\0')
	{
		g_asm->flag_comment = 0;
		g_asm->flag_name = 0;
	}	
	else
		close_with_error("Syntax error at token [TOKEN][003:001] LABEL \"l2:\" || INSTRUCTION \"sti\" || REGISTER \"r1\"....");
}