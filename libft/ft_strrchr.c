/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:02:29 by hharvey           #+#    #+#             */
/*   Updated: 2018/11/22 18:54:36 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	smbl;

	i = 0;
	smbl = (char)c;
	while (s[i])
		i++;
	while (i != -1)
	{
		if (s[i] == smbl)
			return ((char*)s + i);
		i--;
	}
	return (0);
}
