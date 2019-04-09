/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:47:42 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 10:59:34 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_right_label(int i, char *label)
{
	int		j;
	int		counter;

	j = -1;
	counter = 0;
	while (++j < INDEX)
	{
		if (ft_strequ(label, g_struct[j]->label) == 1)
		{
			if (j < i)
				while (j < i)
					counter -= g_struct[j++]->byte;
			else
				while (j >= i)
					counter += g_struct[j--]->byte;
			return (counter);
		}
	}
	error_no_label(label, i);
	return (0);
}

void	write_arg_to_pre_matrix(int i, int j, int *k, char *pre_matrix)
{
	if (j == 1)
	{
		g_asm->shift = 6;
		handle_arg(g_struct[i]->arg[0], i, k, pre_matrix);
	}
	else if (j == 2)
	{
		g_asm->shift = 4;
		handle_arg(g_struct[i]->arg[1], i, k, pre_matrix);
	}
	else
	{
		g_asm->shift = 2;
		handle_arg(g_struct[i]->arg[2], i, k, pre_matrix);
	}
}

void	write_to_dir_byte_arg(int i, int *k, char *pre_matrix)
{
	char	*temp;
	int		j;

	j = 0;
	while (++j <= g_op_tab[g_struct[i]->id_in_tab].var_count)
	{
		write_arg_to_pre_matrix(i, j, k, pre_matrix);
		if (g_op_tab[g_struct[i]->id_in_tab].kod_tipov_argumenta == 1)
		{
			temp = ft_itoa_base(g_struct[i]->octet, 16, 1);
			if (ft_strlen(temp) == 1)
				pre_matrix[3] = temp[0];
			else
			{
				pre_matrix[2] = temp[0];
				pre_matrix[3] = temp[1];
			}
			ft_strdel(&temp);
		}
	}
}

void	realise_algorithm(void)
{
	int		i;
	int		j;
	int		k;
	char	*pre_matrix;

	i = -1;
	while (++i < INDEX)
	{
		if (g_struct[i]->command != NULL)
		{
			pre_matrix = ft_strnew(g_struct[i]->byte * 2);
			ft_memset(pre_matrix, '0', g_struct[i]->byte * 2);
			pre_matrix[1] = (g_op_tab[g_struct[i]->id_in_tab].id > 9) ?
				g_op_tab[g_struct[i]->id_in_tab].id % 10 + 'A' :
					g_op_tab[g_struct[i]->id_in_tab].id + '0';
			k = (g_op_tab[g_struct[i]->id_in_tab].kod_tipov_argumenta
						== 1) ? 4 : 2;
			write_to_dir_byte_arg(i, &k, pre_matrix);
			j = -1;
			while (pre_matrix[++j] != '\0')
				CODE[g_asm->i++] = pre_matrix[j];
			ft_strdel(&pre_matrix);
		}
	}
}
