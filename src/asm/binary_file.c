/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:11:06 by kkihn             #+#    #+#             */
/*   Updated: 2019/04/09 13:05:13 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_binary_code(int fd, char *str, int size)
{
	int				i;
	unsigned char	octet;

	i = 0;
	while (i < size)
	{
		str[i] -= (str[i] >= '0' && str[i] <= '9') ? 48 : 55;
		str[i + 1] -= (str[i + 1] >= '0' && str[i + 1] <= '9')
				? 48 : 55;
		octet = (str[i] << 4) | str[i + 1];
		write(fd, &octet, 1);
		i += 2;
	}
}

void	make_binary(void)
{
	int	fd;
	int	i;

	i = -1;
	if ((fd = open(g_asm->binary_name, O_CREAT | O_TRUNC | O_WRONLY,
			S_IREAD | S_IWRITE)) == -1)
		close_with_error("Error with file");
	while (++i < 7)
		write_binary_code(fd, g_asm->matrix[i], ft_strlen(g_asm->matrix[i]));
	close(fd);
}
