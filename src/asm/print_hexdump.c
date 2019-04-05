/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexdump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:05:06 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/05 15:28:22 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void print_hexdump(void)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	len = 8;
	k = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 32)
		{
			if (len != 0)
			{
				ft_printf("%c%c "BC_DEFAULT, g_asm->matrix[i][k], g_asm->matrix[i][k + 1]);
				j += 2;
				len -=2;
				k += 2;
				if (len == 0 && i == 6)
				{
					ft_printf("\n");
					return ;
				}
			}
			if (len == 0)
			{
				i++;
				k = 0;
				len = ft_strlen(g_asm->matrix[i]);
			}	  
		}
		ft_printf("\n");
	}
}

void print_hexdump_color(void)
{

}