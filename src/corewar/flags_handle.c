/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:08:39 by sdremora          #+#    #+#             */
/*   Updated: 2019/04/09 16:16:59 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_flag_nb(char *str)
{
	long long int	nb;

	nb = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			print_usage();
		str++;
	}
	if (*str == 0)
		print_usage();
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - '0';
		if (nb > 2147483647)
			print_usage();
		str++;
	}
	if (*str != 0)
		print_usage();
	return (nb);
}

static int	get_num_flag(char *str)
{
	if (ft_strequ(str, "-a"))
		return (F_A);
	if (ft_strequ(str, "-dump"))
		return (F_DUMP);
	if (ft_strequ(str, "-d"))
		return (F_D);
	if (ft_strequ(str, "-s"))
		return (F_S);
	if (ft_strequ(str, "-v"))
		return (F_V);
	if (ft_strequ(str, "-n"))
		return (F_N);
	if (ft_strequ(str, "--stealth"))
		return (F_STEALTH);
	if (ft_strequ(str, "-vis"))
		return (F_VIS);
	return (-1);
}

int			handle_flag(char **argv, int *pos, int argc, t_arena *arena)
{
	int i;

	if ((i = get_num_flag(argv[*pos])) >= 0)
	{
		if (i >= F_D)
		{
			*pos += 1;
			if (*pos < argc)
			{
				arena->flags[i] = get_flag_nb(argv[*pos]);
			}
			else
				print_usage();
		}
		else
			arena->flags[i] = 1;
		return (1);
	}
	return (0);
}
