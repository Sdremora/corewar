/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:47:42 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/05 15:12:20 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_right_label(int i, char *label)
{
	int					j;
	int					counter;

	j = -1;
	counter = 0;
	while(++j < INDEX)
	{
		if (ft_strequ(label, g_struct[j].label) == 1)
		{
			if (j < i)
				while (j < i)
					counter -= g_struct[j++].byte;
			else
				while (j >= i)
					counter += g_struct[j--].byte;
			return (counter);
		}
	}
	//error - no label;
	return (0);
}



void		write_arg_to_pre_matrix(int i, int j, int *k, char *pre_matrix)
{	
	if (j == 1)
		handle_arg(g_struct[i].arg[0], i, k, pre_matrix, 6);		
	else if (j == 2)
		handle_arg(g_struct[i].arg[1], i, k, pre_matrix, 4);
	else
		handle_arg(g_struct[i].arg[2], i, k, pre_matrix, 2);
}

void    realise_algorithm(void)
{
    int     i;
    int     j;
	int		k;
    char    *pre_matrix;
	char	*temp;
	int		ind;

    i = -1;
	while (++i < INDEX)
    {
        if (g_struct[i].command != NULL)
		{
			j = 0;
			pre_matrix = ft_strnew(g_struct[i].byte * 2);
			ft_memset(pre_matrix, '0', g_struct[i].byte * 2);
			pre_matrix[1] = (g_op_tab[g_struct[i].id_in_tab].id > 9) ?
				g_op_tab[g_struct[i].id_in_tab].id % 10 + 'A' :
					g_op_tab[g_struct[i].id_in_tab].id + '0';
			k = (g_op_tab[g_struct[i].id_in_tab].kod_tipov_argumenta == 1) ? 4 : 2;
			while(++j <= g_op_tab[g_struct[i].id_in_tab].var_count)
			{
				write_arg_to_pre_matrix(i, j, &k, pre_matrix);
				if (g_op_tab[g_struct[i].id_in_tab].kod_tipov_argumenta == 1)
				{
					temp = ft_itoa_base(g_struct[i].octet, 16, 1);
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
			ind = -1;
			while (pre_matrix[++ind] != '\0')
				CODE[g_asm->i++] = pre_matrix[ind];
			ft_strdel(&pre_matrix);
		}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    }
}