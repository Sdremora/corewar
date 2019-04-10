/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:20:54 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/10 13:39:57 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			skip_whitespaces_com(void)
{
	while (g_asm->buf[g_asm->i] == ' ' || g_asm->buf[g_asm->i] == '\t')
		g_asm->i++;
	if (g_asm->buf[g_asm->i] == COMMENT_CHAR)
		while (g_asm->buf[g_asm->i] != '\n' && g_asm->buf[g_asm->i] != '\0')
			g_asm->i++;
}

void			check_last_char(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (str[i] == ',')
		syntax_error(5);
}

static int		ft_addworld(char **dest, char *str, int count_chars)
{
	int		i;
	int		j;

	j = 0;
	while (str[count_chars] == SEPARATOR_CHAR && str[count_chars] != '\0')
		count_chars++;
	i = count_chars;
	while (str[i] != SEPARATOR_CHAR && str[i] != '\0')
		i++;
	if (!(*dest = ft_strnew(i - count_chars)))
		return (-1);
	while (str[count_chars] == ' ' || str[count_chars] == '\t')
		count_chars++;
	while (count_chars < i)
	{
		if (str[count_chars] != SEPARATOR_CHAR && str[count_chars] != '\0')
			(*dest)[j++] = str[count_chars];
		count_chars++;
	}
	j--;
	while ((*dest)[j] == ' ' || (*dest)[j] == '\t')
		j--;
	(*dest)[++j] = '\0';
	return (i);
}

static int		count_words(char *str, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char			**split(char const *str)
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
	word = count_words((char *)str, SEPARATOR_CHAR);
	check_last_char((char *)str);
	count_chars = 0;
	if (!(array = malloc(sizeof(char*) * (word + 1))))
		return (0);
	while (i < word)
	{
		if ((extra = ft_addworld(&array[i], (char *)str, count_chars)) == -1)
			close_with_error("Error by malloc");
		count_chars = extra;
		i++;
	}
	array[i] = NULL;
	return (array);
}
