/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:58:45 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 15:48:34 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


// int		find_name(char **line)
// {
// 	char	**array;
// 	char	*temp;
// 	int		i;
// 	int		j;
	
// 	i = 0;
// 	array = ft_split_whitespaces(*line);
// 	if (ft_strequ(array[0], ".name") == 1)
// 	{
// 		if (g_asm->flag_name == 1)
// 			close_with_error("syntax error");
// 		g_asm->flag_name = 1;
// 		i = ft_strlen(array[1]);
// 		if (array[1][0] != '"' && array[1][i - 1] == '"')
// 			find_position_error_lex_name_comment(line);
// 		else if (array[1][0] != '"' && array[1][i - 1] != '"')
// 			close_with_error("syntax error");
// 		if (array[1][i - 1] != '"')
// 			close_with_error("syntax error");
// 		if (ft_strlen(array[1]) > PROG_NAME_LENGTH / 2)
// 			close_with_error("Champion name too long (Max length 128)");
// 		if (array[1][0] == '\0')
// 			NAME[0] = '\0';
// 		write_name_comment_to_matrix(array[1], NAME);
// 		if (array[2] != '\0' && array[2][0] != '#')
// 			close_with_error("syntax error");
// 		i = -1;
// 		while (array[++i] != '\0')
// 			ft_strdel(&array[i]);
// 		return (1);
// 	}
// 	return (0);
// }

// int		find_comment(char **line)
// {
// 	char	**array;
// 	int		i;
// 	char *temp;
// 	int j;
	
// 	i = 0;
// 	array = ft_split_whitespaces(*line);
// 	if (ft_strequ(array[0], ".comment") == 1)
// 	{
// 		if (g_asm->flag_comment == 1)
// 			close_with_error("syntax error");
// 		g_asm->flag_comment = 1;
// 		i = ft_strlen(array[1]);
// 		if (array[1][0] != '"' && array[1][i - 1] == '"')
// 			find_position_error_lex_name_comment(line);
// 		else if (array[1][0] != '"' && array[1][i - 1] != '"')
// 			close_with_error("syntax error");
// 		if (array[1][i - 1] != '"')
// 			close_with_error("syntax error");
// 		if (ft_strlen(array[1]) > COMMENT_LENGTH / 2)
// 			close_with_error("too long (Max length 2048)");
// 		write_name_comment_to_matrix(array[1], COMMENT);
// 		if (array[2] != '\0' && array[2][0] != '#')
// 			close_with_error("syntax error");
// 		i = -1;
// 		while (array[++i] != '\0')
// 			ft_strdel(&array[i]);
// 		return (1);
// 	}
// 	return (0);
// }

void    write_name_comment_to_matrix(char i, char *matrix_element, int j)
{
	char	*temp;

	temp = ft_itoa_unsize_base(i, 16);
	if (i < 16 && i != 34)
		matrix_element[j + 1] = temp[0];
	else if (i >= 16)
	{
		matrix_element[j] = temp[0];
		matrix_element[j + 1] = temp[1];
	}
	ft_strdel(&temp);
}
 
void		find_name_comment(char	*buf)
{
	int		counter;

	if (ft_strnequ(".name", &buf[g_asm->i], 5) != 0)
	{
		if (g_asm->flag_name == -1)
			g_asm->flag_name = 1;
		else if (g_asm->flag_name == 1)
		{
			ft_putstr("ERROR1");
			exit(0);
		}
		g_asm->i += 5;
		skip_whitespaces(buf);
		if (buf[g_asm->i] != '"')
		{
			ft_putstr("ERROR2");
			exit(0);
		}
		g_asm->i++;
		counter = 0;
		while (buf[g_asm->i] != '"' && buf[g_asm->i] != '\0')
		{
			printf("|||||\n");
			counter += 2;
			if (counter > PROG_NAME_LENGTH)
			{
				ft_putstr("ERROR3");
				exit(0);
			}
			write_name_comment_to_matrix(buf[g_asm->i], NAME, counter - 2);
			g_asm->i++;
		}
	}
	else if (ft_strnequ(".comment", &buf[g_asm->i], 8) != 0)
	{
		if (g_asm->flag_comment == -1)
			g_asm->flag_comment = 1;
		else if (g_asm->flag_comment == 1)
		{
			ft_putstr("ERROR4");
			exit(0);
		}	
		g_asm->i += 8;
		skip_whitespaces(buf);
		if (buf[g_asm->i] != '"')
		{
			ft_putstr("ERROR5");
			exit(0);
		}
		counter = 0;
		g_asm->i++;
		while (buf[g_asm->i] != '"' && buf[g_asm->i] != '\0')
		{
			counter += 2;
			if (counter > COMMENT_LENGTH)
			{
				ft_putstr("ERROR6");
				exit(0);
			};
			write_name_comment_to_matrix(buf[g_asm->i], COMMENT, counter - 2);
			g_asm->i++;
		}
	}
	else
	{
		ft_putstr("ERROR7");
		exit(0);
	}
	
}