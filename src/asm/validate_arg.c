/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:54:20 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/29 16:48:54 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_register(char *array, int element)
{
	int		i;
	int		value;

	i = 0;
	while (array[++i] != '\0')
	{
		if (array[i] < '0' || array[i] > '9')
			return(0);
	}
	value = atoi(&array[1]);
	if (value > REG_NUMBER || value <= 0)
		return (0);
	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(g_struct[INDEX].command, g_op_tab[i].name) == 1)
		{
			if ((1 & g_op_tab[i].args[element]) == 0)
				return (0);
			return (1);
		}
	}
	return (1);
}

int		check_direct(char *array, int element)
{
	int		i;

	i = -1;
	if (array[1] == LABEL_CHAR)
	{
		while (array[++i] != '\0')
		{
			if (ft_strchr(LABEL_CHARS, array[i]) == 0)
			{
				//g_asm->i = g_asm->i - ft_strlen(array) + i;
				return (0);
			}	
		}
	}
	else if ((array[1] >= '0' && array[1] <= '9') || array[1] == '-')
	{
		i = -1;
		if (array[1] == '-')
			i++;
		while (array[i] != '\0')
		{
			if (array[1] < '0' || array[1] > '9')
				return (0);
		}
	}
	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(g_struct[INDEX].command, g_op_tab[i].name) == 1)
		{
			if ((2 & g_op_tab[i].args[element]) == 0)
				return (0);
			return (1);
		}
	}
	return (1);



}

int     check_if_command_has_arg(char **array)
{
    int i;

    i = -1;
    while (++i < 3)
    {
        if (array[i][0] == 'r')
		{
			if (!(check_register(array[i], i)))
				return (-1);
		}
        else if (array[i][0] == DIRECT_CHAR)
		{
			if (!(check_direct(array[i], i)))
				return (-1);
		}
		else if ((array[i][0] >= '0' && array[i][0] <= '9') ||
				array[i][0] == '-' || array[i][0] == LABEL_CHAR) 
		{
			//if (!(check_indirect(array[i], i)))
				return (-1);
		}
		else
			return (0);
    }
    return(1);
}