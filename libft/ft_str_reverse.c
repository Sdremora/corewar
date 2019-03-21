/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:25:11 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/06 12:04:15 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Разворачивает строку.
**	12345 -> 54321
*/

void	ft_str_reverse(char *str)
{
	size_t	left;
	size_t	right;
	char	temp;

	if (str == NULL)
		return ;
	left = 0;
	right = ft_strlen(str) - 1;
	while (left < right)
	{
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}
