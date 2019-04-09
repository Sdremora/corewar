/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_for_writing_commands_find.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:01:16 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 13:43:20 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Here we write some small and utility functions for writing_command_to_struct
*/

int	count_chars(void)
{
	int	i;
	int	counter;

	i = g_asm->i;
	counter = 0;
	while (BUFFER[i] != '\n' && BUFFER[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
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

int	find_id_in_tab(void)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(g_struct[INDEX]->command, g_op_tab[i].name) == 1)
			return (i);
	}
	return (-1);
}

int	count_args_size(void)
{
	int		counter;
	int		i;

	i = g_asm->i;
	counter = 0;
	while (BUFFER[i] != '\n' && BUFFER[i] != '\0')
	{
		i++;
		counter++;
	}
	return (counter);
}
