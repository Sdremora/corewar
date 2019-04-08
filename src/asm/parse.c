/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:16:12 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/08 12:16:41 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
//Error by parsing schould be other, we need to think abou how to find right position of false element

void	skip_whitespaces(void)
{
	while (g_asm->buf[g_asm->i] == ' ' || g_asm->buf[g_asm->i] == '\t')
		g_asm->i++;
}

void	skip_comment_and_spaces(void)
{
	while ((g_asm->buf[g_asm->i] <= 32 || g_asm->buf[g_asm->i] == COMMENT_CHAR) && g_asm->buf[g_asm->i] != '\0')
	{
		if (g_asm->buf[g_asm->i] == '\n')
			g_asm->str_counter++;
		if (g_asm->buf[g_asm->i] == COMMENT_CHAR)
		{
			while (g_asm->buf[g_asm->i] != '\n' && g_asm->buf[g_asm->i] != '\0')
				g_asm->i++;
		}
		else
			g_asm->i++;
	}
}

void    parse_from_file(int argc, char **argv)
{
    int     ret;
	int		fd;

	fd = open(argv[argc - 1], O_RDONLY);
	while ((ret = read(fd, g_asm->buf, BUFF)) > 0)
	{
		g_asm->buf[ret] = '\0';
		g_asm->i = 0;
		while(g_asm->buf[g_asm->i] != '\0')
		{
			skip_comment_and_spaces();
			if (g_asm->flag_comment == -1 || g_asm->flag_name == -1)
				find_name_comment();
			//printf("%s\n", &BUFFER[g_asm->i]);
			skip_comment_and_spaces();
			if (g_asm->flag_comment > -1 && g_asm->flag_name > -1)
			{
				if (g_asm->buf[g_asm->i] == '\0')
					syntax_error(6);
				if (g_asm->flag_name == 0)
					length_error(1);
				else if (g_asm->flag_comment == 0)
					length_error(2);
				write_labels_commands();
			}
			// g_asm->i++;
		}
	}
	if (ret < 0)
		close_with_error("Can't read source file\n");
	// else if (ret == 0 && (g_asm->buf || g_asm->buf[i] != '\n'))
	// 	error_by_parsing(); NO \n!
	close(fd);
	return ;
}