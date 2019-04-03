/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_for_writing_commands_to_struct.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:01:16 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/03 13:11:40 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
** Here we write some small and utility functions for writing_command_to_struct
*/

int     count_chars(void)
{
    int     i;
	int		counter;

    i = g_asm->i;
	counter = 0;
    while (BUFFER[i] != '\n' && BUFFER[i] != '\0')
	{
        counter++;
		i++;
	}	
    return (counter);
}

int		check_if_command_exist(char *temp)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(temp, g_op_tab[i].name) == 1)
			return (1);
	}
	return (0);
}

int		check_if_label_exist(char *temp)
{
	int		i;
	i = -1;
	while (++i < INDEX)
	{
		if (ft_strequ(temp, g_struct[i].label) == 1)
			return (0);
	}
	return (1);
}

 int	find_flag(char *array)
 {
	if (array[0] == 'r')
	{
		if (check_register(array, -1))
			return (1);
	}		
	else if (array[0] == DIRECT_CHAR)
	{
		if (check_direct_or_indirect(array, -1, 1))
			return (2);
	}		
	else if ((array[0] >= '0' && array[0] <= '9') ||
			array[0] == '-' || array[0] == LABEL_CHAR)
	{
		if (check_direct_or_indirect(array, -1, 0))
			return (3);
	}
	return (1);
}
