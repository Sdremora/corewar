/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:40:56 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/10 13:39:21 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_position_in_str(void)
{
	int		i;

	i = 0;
	if (BUFFER[g_asm->i] == '\n' && g_asm->i != 0)
	{
		g_asm->i--;
		i += 2;
	}
	while (BUFFER[g_asm->i] != '\n' && g_asm->i != 0)
	{
		g_asm->i--;
		i++;
	}
	return (i);
}

int		find_position_in_str_for_instruction(char *instruction)
{
	int		i;
	int		counter;
	char	*temp;

	if (BUFFER[g_asm->i] == '\n' && g_asm->i != 0)
		g_asm->i--;
	while (g_asm->buf[g_asm->i] != '\n' && g_asm->i != 0)
		g_asm->i--;
	i = 0;
	g_asm->i++;
	counter = g_asm->i;
	while (BUFFER[g_asm->i] != '\n' && BUFFER[g_asm->i] != '\0')
	{
		i++;
		g_asm->i++;
	}
	temp = ft_strnstr((char *)&BUFFER[counter], instruction, i);
	counter = 0;
	while (temp[counter] != '\n' && temp[counter] != '\0')
		counter++;
	return (i - counter + 1);
}

int		find_label_index(char *label, int *flag)
{
	int i;
	int j;

	i = -1;
	while (BUFFER[++i])
	{
		j = 0;
		if (BUFFER[i] == label[j] || !label[j])
		{
			while (label[j] == BUFFER[i + j] && BUFFER[i + j])
				j++;
			if (label[j] == '\0' || label[j] == ' ')
			{
				j = 0;
				while (BUFFER[i] != '\n' && i != 0)
				{
					i--;
					j++;
				}
				*flag = i;
				return (j);
			}
		}
	}
	return (0);
}
