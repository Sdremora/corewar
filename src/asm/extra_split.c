/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:20:54 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/03 16:51:17 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	if (!(*dest = (char*)malloc(sizeof(char) * (i - count_chars + 1))))
		return (-1);
	while (count_chars < i)
	{
		if (str[count_chars] != ' ' && str[count_chars] != '\t')
			(*dest)[j++] = str[count_chars];
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
		if((extra = ft_addworld(&array[i], (char *)str, count_chars, c)) == -1)
			close_with_error("Error by malloc");
		count_chars = extra;
		i++;
	}
	array[i] = NULL;
	return (array);
}