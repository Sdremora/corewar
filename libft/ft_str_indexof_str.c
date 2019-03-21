/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_indexof_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:36:57 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/06 12:09:50 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Ищет в строке haystack строку needle.
**	Если находит её -> возвращает индекс начала строки needle в haystack
**	Если не находит -> вернет -1
*/

int	ft_str_indexof_str(const char *haystack, const char *needle)
{
	int	haystack_len;
	int	needle_len;
	int	i;
	int	n;
	int	end;

	if (needle == NULL)
		return (0);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	end = haystack_len - needle_len + 1;
	n = 0;
	while (n < end)
	{
		if (haystack[n] == *needle)
		{
			i = 0;
			while ((i < needle_len) && (haystack[n + i] == needle[i]))
				i++;
			if (i == needle_len)
				return (n);
		}
		n++;
	}
	return (-1);
}
