/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:16:12 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 17:38:17 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		count_all_str(void)
{
	int		i;
	int		counter;

	i = g_asm->i;
	counter = 1;
	while (BUFFER[i] != '\0')
	{
		if (BUFFER[i] == '\n')
			counter++;
		i++;
	}
	return (counter);
}

void	skip_whitespaces(void)
{
	while (g_asm->buf[g_asm->i] == ' ' || g_asm->buf[g_asm->i] == '\t')
		g_asm->i++;
}

void	skip_comment_and_spaces(void)
{
	while ((g_asm->buf[g_asm->i] <= 32 ||
		g_asm->buf[g_asm->i] == COMMENT_CHAR) &&
		g_asm->buf[g_asm->i] != '\0')
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

void	parse_buffer(void)
{
	while (g_asm->buf[g_asm->i] != '\0')
	{
		skip_comment_and_spaces();
		if (g_asm->flag_comment == -1 || g_asm->flag_name == -1)
			find_name_comment();
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
	}
}

void	parse_from_file(int argc, char **argv)
{
	int		ret;
	int		fd;

	fd = open(argv[argc - 1], O_RDONLY);
	while ((ret = read(fd, g_asm->buf, BUFF + 1)) > 0)
	{
		g_asm->buf[ret] = '\0';
		(ret > BUFF) ? close_with_error("File is too big") : 0;
		g_asm->i = 0;
		parse_buffer();
	}
	if (ret < 0)
		close_with_error("Can't read source file");
	else if (ret == 0 && ft_strlen((char*)BUFFER) == 0)
		syntax_error(6);
	close(fd);
	return ;
}
