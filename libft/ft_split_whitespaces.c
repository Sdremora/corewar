/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 19:48:47 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 09:20:02 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_addworld(char **dest, char *str, int count_chars)
{
	int		i;
	int		j;

	j = 0;
	i = count_chars;
	while ((str[i] == '\n' || str[i] == ' '
			|| str[i] == '\t') && str[i] != '\0')
	{
		i++;
		count_chars++;
	}
	while ((str[i] != '\n' && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\0') && str[i] != '\0')
		i++;
	if (!(*dest = (char*)malloc(sizeof(char) * (i - count_chars + 1))))
		exit(0);
	while (count_chars < i)
	{
		(*dest)[j] = str[count_chars];
		count_chars++;
		j++;
	}
	(*dest)[j] = '\0';
	return (i);
}

int		count_words(char *str)
{
	int		i;
	int		counter;
	int		temp;

	i = 0;
	counter = 0;
	temp = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\n' && str[i] != ' '
			&& str[i] != '\t')
			temp = 1;
		else if ((str[i] == '\n'
			|| str[i] == ' ' || str[i] == '\t') && temp != 0)
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

char	**ft_split_whitespaces(char *str)
{
	int		i;
	int		word;
	char	**array;
	int		count_chars;
	int		extra;

	i = 0;
	extra = 0;
	word = count_words(str);
	count_chars = 0;
	if (!(array = malloc(sizeof(char*) * (word + 1))))
		exit(0);
	while (i < word)
	{
		extra = ft_addworld(&array[i], str, count_chars);
		count_chars = extra;
		i++;
	}
	array[i] = (char*)0;
	return (array);
}
