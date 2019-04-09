/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexdump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:05:06 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/09 16:59:46 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_line(char *str, int *i, int *line_nbr)
{
	int j;

	j = 0;
	while (str[j] && str[j + 1])
	{
		if (*i % 32 == 0)
		{
			ft_printf("\n");
			ft_printf("%07x\t", *line_nbr);
			(*line_nbr)++;
		}
		ft_printf("%c%c ", str[j], str[j + 1]);
		j += 2;
		*i += 2;
	}
}

void	print_hexdump_second(int i, int line_nbr)
{
	ft_printf(BC_MAGENTA);
	ft_printf(BC_BOLD);
	print_line(CODE, &i, &line_nbr);
	ft_printf(BC_DEFAULT);
	ft_printf("\n");
}

void	print_hexdump(void)
{
	int i;
	int line_nbr;

	i = 0;
	line_nbr = 0;
	ft_printf(BC_MAGENTA);
	ft_printf(BC_BOLD);
	print_line(HEADER, &i, &line_nbr);
	ft_printf(BC_DEFAULT);
	ft_printf(BC_YELLOW);
	print_line(NAME, &i, &line_nbr);
	ft_printf(BC_DEFAULT);
	ft_printf(BC_BOLD);
	print_line(ZERO1, &i, &line_nbr);
	ft_printf(BC_DEFAULT);
	ft_printf(BC_BG_MAGENTA);
	ft_printf(BC_BOLD);
	print_line(SIZE, &i, &line_nbr);
	ft_printf(BC_BG_DEFAULT);
	ft_printf(BC_GREEN);
	print_line(COMMENT, &i, &line_nbr);
	ft_printf(BC_DEFAULT);
	ft_printf(BC_BOLD);
	print_line(ZERO2, &i, &line_nbr);
	print_hexdump_second(i, line_nbr);
}
