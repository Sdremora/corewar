/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:54:20 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/01 12:23:35 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
// #9223372036854775807 - max value of T_IND or T_DIR,
// if our value is more we use this one

int check_arg_type(int element, int type)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(g_struct[INDEX].command, g_op_tab[i].name) == 1)
		{
			if ((type & g_op_tab[i].args[element]) == 0)
				return (0);
			return (1);
		}
	}
	return (0);
}

int		check_register(char *array, int element)
{
	int		i;
	int		value;

	i = 0;
	while (array[++i] != '\0')
	{
		if (array[i] < '0' || array[i] > '9')
			return (0);
	}
	value = atoi(&array[1]);
	if (value > REG_NUMBER || value <= 0)
		return (0);
	if (!(check_arg_type(element, 1)))
		return( 0);
	return (1);
}

int		check_direct_or_indirect(char *array, int element, int flag)
{
	int		i;

	i = -1;
	if (array[flag] == LABEL_CHAR)
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
	else if ((array[flag] >= '0' && array[flag] <= '9') || array[flag] == '-')
	{
		i = -1;
		if (array[flag] == '-')
			i++;
		while (array[i] != '\0')
		{
			if (array[i] < '0' || array[i] > '9')
				return (0);
		}
	}
	if (!(check_arg_type(element, 2)))
		return (0);
	return (1);
}

// int		check_indirect(char *array, int element)
// {
// 	int		i;

// 	i = -1;
// 	if (array[0] == LABEL_CHAR)
// 	{
// 		while (array[++i] != '\0')
// 		{
// 			if (ft_strchr(LABEL_CHARS, array[i]) == 0)
// 			{
// 				//g_asm->i = g_asm->i - ft_strlen(array) + i;
// 				return (0);
// 			}	
// 		}
// 	}
// 	else if ((array[0] >= '0' && array[0] <= '9') || array[0] == '-')
// 	{
// 		i = -1;
// 		if (array[0] == '-')
// 			i++;
// 		while (array[i] != '\0')
// 		{
// 			if (array[i] < '0' || array[i] > '9')
// 				return (0);
// 		}
// 	}
// 	if (!(check_arg_type(element, 4)))
// 		return (0);
// 	return (1);
// }

int     check_if_command_has_arg(char **array)
{
    int i;

    i = -1;
    while (++i < g_op_tab[g_struct[INDEX].id_in_tab].var_count)
    {
        if (array[i][0] == 'r')
		{
			if (!(check_register(array[i], i)))
				return (-1);
		}
        else if (array[i][0] == DIRECT_CHAR)
		{
			if (!(check_direct_or_indirect(array[i], i, 1)))
				return (-1);
		}
		else if ((array[i][0] >= '0' && array[i][0] <= '9') ||
				array[i][0] == '-' || array[i][0] == LABEL_CHAR) 
		{
			if (!(check_direct_or_indirect(array[i], i, 0)))
				return (-1);
		}
		else
			return (0);
    }
	return(1);
}
