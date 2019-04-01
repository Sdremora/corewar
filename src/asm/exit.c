/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:52:48 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/01 15:41:27 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    usage(void)
{
    ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n");
    ft_putstr("    -a : Instead of creating a .cor file, outputs a stripped and\
                     annotated version of the code to the standard output\n");
    exit(0);
}

void	del_all_struct(void)
{
	int		i;
	if (g_asm)
	{
		if (g_asm->binary_name)
			ft_strdel(&g_asm->binary_name);
		if (g_asm->matrix)
		{
			i = -1;
			while (++i < 6)
				ft_strdel(&g_asm->matrix[i]);
			free(g_asm->matrix);
		}
		free(g_asm);
	}
}

void	close_with_error(char *str)
{
	del_all_struct();
	ft_putstr(str);
	ft_putstr("\n");
	exit(0);
}
