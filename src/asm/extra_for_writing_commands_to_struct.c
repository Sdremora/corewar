/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_for_writing_commands_to_struct.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:01:16 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/28 19:29:27 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
# include "corewar.h"
/*
** Here we write some small and utility functions for writing_command_to_struct
*/

int     count_chars(void)
{
    int     i;

    i = g_asm->i;
    while (BUFFER[i] != '\n' && BUFFER[i] != '\0')
        i++;
    return (i);
}

// int		check_if_command_exist(char *temp)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < 16)
// 	{
// 		if (ft_strequ(temp, g_op_tab[i].name) == 1)
// 			return (1);
// 	}
// 	return (0);
// }

int		check_if_label_exist(char *temp)
{
	int		i;
	int		n;
	i = -1;
	n = 0; //количество элементов у массиве структур или меньше текушего индексаж
	while (++i < n)
	{
		if (ft_strequ(temp, g_struct[i].label) == 1)
			return (0);
	}
	return (1);
}
