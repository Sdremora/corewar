/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:40:56 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/08 12:44:57 by kkihn            ###   ########.fr       */
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
	temp = ft_strnstr(&BUFFER[counter], instruction, i);
	counter = 0;
	while (temp[counter] != '\n' && temp[counter] != '\0')
		counter++;
	return(i - counter + 1);
}