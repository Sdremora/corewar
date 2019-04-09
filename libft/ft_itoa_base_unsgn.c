/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsgn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:25:27 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/09 17:48:22 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_get_itoa_len_uns(unsigned long long int nb, int base)
{
	int					res;

	if (!nb)
		return (1);
	res = 0;
	while (nb)
	{
		nb /= base;
		res++;
	}
	return (res);
}

unsigned char	*ft_itoa_base_unsgn(unsigned long long int nb,
												int base, int isbig)
{
	int					len;
	unsigned char		*res;
	int					i;
	static char			base_ar[33] = "";

	if (!base_ar[0])
		ft_strcpy(base_ar, "0123456789abcdef0123456789ABCDEF");
	i = 1;
	len = ft_get_itoa_len_uns(nb, base);
	if (!(res = ft_memalloc(len + 1)))
		return (0);
	while (nb / base)
	{
		res[len - i] = base_ar[ft_abs(nb % base) + isbig * 16];
		nb /= base;
		i++;
	}
	res[len - i] = base_ar[ft_abs(nb % base) + isbig * 16];
	return (res);
}
