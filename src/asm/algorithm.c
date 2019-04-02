/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:47:42 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/02 16:03:00 by mnarbert         ###   ########.fr       */
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
			{
				while (j < i)
				{
					counter -= g_struct[j].byte;
					j++;
				}
			}
			else
			{
				while (j > i)
				{
					counter += g_struct[j].byte;
					j--;
				}
			}
			return (counter);
		}
	}
	//error - no label;
	return (0);
}

void		write_arg_to_pre_matrix(int i, int j, int *k, char *pre_matrix)
{
	long long int		counter;
	char				*temp;
	int					ind;
	
	if (j == 1)
	{	
		counter = find_flag(g_struct[i].arg1);
		g_struct[i].octet = g_struct[i].octet | counter;
		g_struct[i].octet = g_struct[i].octet << 6;
		if (counter == 1)
		{
			counter = ft_atoi_long(&g_struct[i].arg1[1]);
			temp = ft_itoa_base(counter, 16, 1);
			if (ft_strlen(temp) == 1)
				pre_matrix[*k + 1] = temp[0];
			else
			{
				pre_matrix[*k] = temp[0];
				pre_matrix[*k + 1] = temp[1];
			}
			*k += 2;
		}
		else if (counter == 2)
		{
			if (g_struct[i].arg1[1] == LABEL_CHAR)
			{
				counter = find_right_label(i, &g_struct[i].arg1[2]);
			}
			else
			{
				counter = ft_atoi_long(&g_struct[i].arg1[1]);
				if (counter < 0)
					counter = (counter * (-1)) ^ 4294967295 + 1;
				temp = ft_itoa_base(counter, 16, 1);
				counter = 4;
				if (g_op_tab[g_struct[i].id_in_tab].t_dir_size_eq_4 == 0)
					counter *= 2;
				*k += counter;\
				ind = ft_strlen(temp);
				while (--ind >= 0 && counter-- > 0)
					pre_matrix[*k--] = temp[ind];
				if (counter > 0)
					*k -= counter;
				if (g_op_tab[g_struct[i].id_in_tab].t_dir_size_eq_4 == 0)
					*k += 8;
				else
					*k += 4;
				
			}
		}
	}
	else if (j == 2)
	{
		counter = find_flag(g_struct[i].arg2);
		g_struct[i].octet = g_struct[i].octet | counter;
		g_struct[i].octet = g_struct[i].octet << 4;
	}
	else
	{
		counter = find_flag(g_struct[i].arg3);
		g_struct[i].octet = g_struct[i].octet | counter;
		g_struct[i].octet = g_struct[i].octet << 2;
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