/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_for_writing_commands_to_struct.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:01:16 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/29 12:51:29 by mnarbert         ###   ########.fr       */
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

static int		ft_addworld(char **dest, char *str, int count_chars, char c)
{
	int		i;
	int		j;

	j = 0;
	i = count_chars;
	while (str[i] == c && str[i] != '\0' && str[i] != '\n')
	{
		i++;
		count_chars++;
	}
	while (str[i] != c && str[i] != '\0' && str[i] != '\n')
		i++;
	*dest = (char*)malloc(sizeof(char) * (i - count_chars + 1));
	while (count_chars < i)
	{
		if (str[count_chars] != ' ' && str[count_chars] != '\t')
		{
			(*dest)[j] = str[count_chars];
			j++;
		}	
		count_chars++;
	}
	(*dest)[j] = '\0';
	return (i);
}

static int		count_words(char *str, char c)
{
	int		i;
	int		counter;
	int		temp;

	i = 0;
	counter = 0;
	temp = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] != c)
			temp = 1;
		else if (str[i] == c && temp != 0 && str[i] != '\n')
		{
			counter++;
			temp = 0;
		}
		i++;
	}
	if (temp != 0)
		counter++;
	return (counter);
}

char			**split(char const *str, char c)
{
	int		i;
	int		word;
	char	**array;
	int		count_chars;
	int		extra;

	i = 0;
	extra = 0;
	if (!str)
		return (NULL);
	word = count_words((char *)str, c);
	count_chars = 0;
	if (!(array = malloc(sizeof(char*) * (word + 1))))
		return (0);
	while (i < word)
	{
		extra = ft_addworld(&array[i], (char *)str, count_chars, c);
		count_chars = extra;
		i++;
	}
	array[i] = NULL;
	return (array);
}