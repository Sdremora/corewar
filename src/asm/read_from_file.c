/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:54:49 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/26 17:16:24 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_binary_name(int argc, char *str)
{
	int		len;
	int		i;
	
	len = ft_strlen(str);
	i = -1;
	if (str[len - 1] != 's' || str[len - 2] != '.')
		usage();
	while (len - 1 != 0 && str[len - 1] != '/')
		len--;
	if (!(g_asm->binary_name = ft_strnew(ft_strlen(str) - len - 1 + 3)))
		close_with_error("Error by malloc\n");
	if (str[len] == '/')
		len++;
	while (str[len] != '.')
		g_asm->binary_name[++i] = str[len++];
	g_asm->binary_name[++i] = '.';
	g_asm->binary_name[++i] = 'c';
	g_asm->binary_name[++i] = 'o';
	g_asm->binary_name[++i] = 'r';
	g_asm->binary_name[++i] = '\0';
}

int		main(int argc, char **argv)
{
	int		len;
	if (argc > 1)
	{
		init();
		write_binary_name(argc, argv[argc - 1]);
		parse_from_file(argc, argv);
	}
	else
		usage();
	return (0);
}