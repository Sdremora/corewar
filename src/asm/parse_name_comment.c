/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:58:45 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 17:10:02 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_name_comment_to_matrix(unsigned char i,
			char *matrix_element, int j)
{
	unsigned char	*temp;

	temp = ft_itoa_base_unsgn(i, 16, 1);
	if (i < 16 && i != 34)
		matrix_element[j + 1] = temp[0];
	else if (i >= 16)
	{
		matrix_element[j] = temp[0];
		matrix_element[j + 1] = temp[1];
	}
	free(temp);
}

int		going_throw_two_quotes(int limit, char *matrix_element)
{
	int		counter;

	skip_whitespaces();
	if (g_asm->buf[g_asm->i] == '\n' || g_asm->buf[g_asm->i] == COMMENT_CHAR)
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
		write_name_comment_to_matrix(g_asm->buf[g_asm->i],
						matrix_element, counter - 2);
		g_asm->i++;
	}
	return (1);
}

void	find(int counter, int length, char *matrix_element)
{
	g_asm->i += counter;
	if (going_throw_two_quotes(length, matrix_element) == -1)
	{
		if (counter == 5)
		{
			g_asm->flag_comment = 1;
			g_asm->flag_name = 0;
		}
		else if (counter == 8)
		{
			g_asm->flag_comment = 0;
			g_asm->flag_name = 1;
		}
	}
	if (g_asm->buf[g_asm->i] == '"')
		g_asm->i++;
}

void	find_name_comment(void)
{
	int len;

	if (ft_strnequ(".name", (char *)&g_asm->buf[g_asm->i], 5) != 0)
	{
		(g_asm->flag_name == 1) ? syntax_error(2) : 0;
		g_asm->flag_name = (g_asm->flag_name == -1) ? 1 : g_asm->flag_name;
		len = PROG_NAME_LENGTH;
		find(5, len * 2, NAME);
	}
	else if (ft_strnequ(".comment", (char *)&g_asm->buf[g_asm->i], 8) != 0)
	{
		(g_asm->flag_comment == 1) ? syntax_error(1) : 0;
		g_asm->flag_comment = (g_asm->flag_comment == -1) ?
				1 : g_asm->flag_comment;
		len = COMMENT_LENGTH;
		find(8, len * 2, COMMENT);
	}
	else if (g_asm->buf[g_asm->i] == '\0')
	{
		g_asm->flag_comment = 0;
		g_asm->flag_name = 0;
	}
	else
		lexical_error();
}
