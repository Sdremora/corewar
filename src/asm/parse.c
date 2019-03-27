/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:16:12 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/26 18:01:20 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    parse_from_file(int argc, char **argv)
{
    char    *line;
    int     ret;
	int		fd;

    line = NULL;
	fd = open(argv[argc - 1], O_RDONLY);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
		
		g_asm->str_counter++;
    }
	if (ret < 0)
		close_with_error("Invalid file\n");
	else if (ret == 0 && (line || line[0] != '\0'))
		error_by_parsing("Syntax error at token [TOKEN] [", 
			ft_strlen(line), "] END \"(null)\"\n");
}