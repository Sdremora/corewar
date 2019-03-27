/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:58:45 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 18:27:41 by mnarbert         ###   ########.fr       */
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
 

void		going_throw_two_quotes(int	limit, char *matrix_element, char *buf)
{
	int		counter;
	skip_whitespaces(buf);
	if (buf[g_asm->i] == '\n' || buf[g_asm->i] == '#')
		syntax_error(5, buf);
	if (buf[g_asm->i] != '"')
		lexical_error(buf);
	g_asm->i++;
	counter = 0;
	while (buf[g_asm->i] != '"' && buf[g_asm->i] != '\0')
	{
		counter += 2;
		if (buf[g_asm->i] == '\n')
			g_asm->str_counter++;
		if (counter > limit)
			close_with_error("Champion name too long (Max length 128 - PROGRAMM_LENGTH)");
		write_name_comment_to_matrix(buf[g_asm->i], matrix_element, counter - 2);
		g_asm->i++;
	}
	if (buf[g_asm->i] == '\0')
		close_with_error("Syntax error at token [TOKEN][002:010] ENDLINE");
}

void		find_name_comment(char	*buf)
{
	if (ft_strnequ(".name", &buf[g_asm->i], 5) != 0)
	{
		if (g_asm->flag_name == -1)
			g_asm->flag_name = 1;
		else if (g_asm->flag_name == 1)
			syntax_error(2, buf);
		g_asm->i += 5;
		going_throw_two_quotes(PROG_NAME_LENGTH, NAME, buf);
	}
	else if (ft_strnequ(".comment", &buf[g_asm->i], 8) != 0)
	{
		if (g_asm->flag_comment == -1)
			g_asm->flag_comment = 1;
		else if (g_asm->flag_comment == 1)
			syntax_error(1, buf);
		g_asm->i += 8;
		going_throw_two_quotes(COMMENT_LENGTH, COMMENT, buf);
	}
	else
		close_with_error("Syntax error at token [TOKEN][003:001] LABEL \"l2:\" || INSTRUCTION \"sti\" || REGISTER \"r1\"....");
}