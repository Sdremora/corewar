/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:25:45 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/06 19:25:48 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_octet(unsigned char p)
{
	static char base[17] = "0123456789abcdef";

	ft_putchar(base[p / 16 % 16]);
	ft_putchar(base[p % 16]);
}

void	print_mem(unsigned int n)
{
	static char base[17] = "0123456789abcdef";

	ft_putchar(base[n / 16 / 16 % 16]);
	ft_putchar(base[n / 16 % 16]);
	ft_putchar(base[n % 16]);
}

void	print_map(unsigned char *map, int n)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % n == 0)
			ft_printf("%06p : ", i);
		print_octet(map[i]);
		if (i % n == n - 1)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
	}
}
