/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:52:48 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 18:19:30 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	usage(void)
{
	ft_putstr("Usage: ./asm [-hex] <sourcefile.s>\n");
	ft_putstr("  -hex :  trasform code to hexdump output\n");
	exit(0);
}

void	del_asm(void)
{
	int		i;

	if (g_asm)
	{
		if (g_asm->binary_name)
			ft_strdel(&g_asm->binary_name);
		if (g_asm->matrix)
		{
			i = -1;
			while (++i < 7)
				ft_strdel(&g_asm->matrix[i]);
			free(g_asm->matrix);
		}
		free(g_asm);
	}
}

void	del_all_struct(void)
{
	int		i;
	int		j;

	if (g_struct)
	{
		i = -1;
		while (++i < g_asm->size_of_struct * 2)
		{
			ft_strdel(&g_struct[i]->label);
			if (g_struct[i]->arg != NULL)
			{
				j = -1;
				while (g_struct[i]->arg[++j] != NULL)
					free(g_struct[i]->arg[j]);
				free(g_struct[i]->arg);
			}
			if (g_struct[i]->command != NULL)
				ft_strdel(&g_struct[i]->command);
			free(g_struct[i]);
		}
		free(g_struct);
	}
	del_asm();
}

void	close_with_error(char *str)
{
	del_all_struct();
	ft_putstr(str);
	ft_putstr("\n");
	exit(0);
}
