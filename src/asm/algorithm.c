/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:47:42 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/02 13:31:52 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_arg_to_pre_matrix(int i, int j, int *k, char *pre_matrix)
{
	int		counter;
	
	if (j == 1)
	{	
		counter = find_flag(g_struct[i].arg1);
		g_struct[i].octet = g_struct[i].octet | counter;
	}
	else if (j == 2)
	{
		counter = find_flag(g_struct[i].arg1);
	}
	else
	{
		counter = find_flag(g_struct[i].arg1);
	}
}

void    realise_algorithm(void)
{
    int     i;
    int     j;
	int		k;
    char    *pre_matrix;

    i = -1;
    while (++i < INDEX)
    {
        j = 0;
        pre_matrix = ft_strnew(g_struct[i].byte * 2);
        ft_memset(pre_matrix, '0', g_struct[i].byte * 2);
        pre_matrix[1] = (g_op_tab[g_struct[i].id_in_tab].id > 9) ?
            g_op_tab[g_struct[i].id_in_tab].id % 10 + 'A' :
                g_op_tab[g_struct[i].id_in_tab].id;
		k = (g_op_tab[g_struct[i].id_in_tab].kod_tipov_argumenta == 1) ? 4 : 2;
        while(++j <= g_op_tab[g_struct[i].id_in_tab].var_count)
        {
			write_arg_to_pre_matrix(i, j, &k, pre_matrix);
        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    }
}