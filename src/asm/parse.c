/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:16:12 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/28 11:37:22 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
//Error by parsing schould be other, we need to think abou how to find right position of false element

void	skip_whitespaces(char *buf)
{
	while (buf[g_asm->i] == ' ' || buf[g_asm->i] == '\t')
		g_asm->i++;
}

void	skip_comment_and_spaces(char *buf)
{
	while ((buf[g_asm->i] < 32 || buf[g_asm->i] == '#') && buf[g_asm->i] != '\0')
	{
		if (buf[g_asm->i] == '\n')
			g_asm->str_counter++;
		if (buf[g_asm->i] == '#')
		{
			while (buf[g_asm->i] != '\n' && buf[g_asm->i] != '\0')
				g_asm->i++;
		}
		else
			g_asm->i++;
	}
}

void    parse_from_file(int argc, char **argv)
{
    char    buf[BUFF];
    int     ret;
	int		fd;

	fd = open(argv[argc - 1], O_RDONLY);
	while ((ret = read(fd, buf, BUFF)) > 0)
	{
		buf[ret] = '\0';
		g_asm->i = 0;
		while(buf[g_asm->i] != '\0')
		{
			skip_comment_and_spaces(buf);
			if (g_asm->flag_comment == -1 || g_asm->flag_name == -1)
				find_name_comment(buf);
			skip_comment_and_spaces(buf);
			if (g_asm->flag_comment > -1 && g_asm->flag_name > -1)
			{
				if (buf[g_asm->i] == '\0')
					syntax_error(6, buf);
				if (g_asm->flag_name == 0)
					length_error(1);
				else if (g_asm->flag_comment == 0)
					length_error(2);
				//printf("name: %s\n\n\n", NAME);
				//printf("comment: %s\n\n\n", COMMENT);
				//exit(0);
			}
			// 	analyse_labels_commands(buf);
			g_asm->i++;
		}
	}
	if (ret < 0)
		close_with_error("Can't read source file\n");
	// else if (ret == 0 && (buf || buf[i] != '\n'))
	// 	error_by_parsing(); NO \n!
	return ;
}