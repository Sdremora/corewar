/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:11:55 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/08 16:03:51 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		handle_first_arg(char *arg, int *k, char *pre_matrix)
{
	char			*temp;
	long long int	counter;

	counter = ft_atoi_long(&arg[1]);
	temp = ft_itoa_base(counter, 16, 1);
	if (ft_strlen(temp) == 1)
		pre_matrix[*k + 1] = temp[0];
	else
	{
		pre_matrix[*k] = temp[0];
		pre_matrix[*k + 1] = temp[1];
	}
	*k += 2;
	ft_strdel(&temp);
}

void		handle_second_arg(char *pre_matrix, int i, char *arg, int *k)
{
	long long int	counter;
	char			*temp;
	int				ind;

	if (arg[1] == LABEL_CHAR)
		counter = find_right_label(i, &arg[2]);
	else
		counter = ft_atoi_long(&arg[1]);
	if (counter < 0)
		counter = ((counter * (-1)) ^ 4294967295) + 1;
	temp = ft_itoa_base(counter, 16, 1);
	counter = (g_op_tab[g_struct[i]->id_in_tab].t_dir_size_eq_4 ==
			0) ? 8 : 4;
	*k += counter - 1;
	ind = ft_strlen(temp);
	while (--ind >= 0 && counter-- > 0)
		pre_matrix[(*k)--] = temp[ind];
	if (counter > 0)
		*k -= counter - 1;
	else
		(*k)++;
	*k += (g_op_tab[g_struct[i]->id_in_tab].t_dir_size_eq_4 == 0) ?
		8 : 4;
	ft_strdel(&temp);
}

void		handle_third_arg(char *pre_matrix, int i, char *arg, int *k)
{
	long long int	counter;
	char			*temp;
	int				ind;

	if (arg[0] == LABEL_CHAR)
		counter = find_right_label(i, &arg[1]);
	else
		counter = ft_atoi_long(arg);
	if (counter < 0)
		counter = ((counter * (-1)) ^ 4294967295) + 1;
	temp = ft_itoa_base(counter, 16, 1);
	counter = 4;
	*k += counter - 1;
	ind = ft_strlen(temp);
	while (--ind >= 0 && counter-- > 0)
		pre_matrix[(*k)--] = temp[ind];
	if (counter > 0)
		*k -= counter - 1;
	else
		(*k)++;
	*k += 4;
	ft_strdel(&temp);
}

void		handle_arg(char *arg, int i, int *k, char *pre_matrix)
{
	long long int	counter;
	unsigned char	oct;

	counter = find_flag(arg);
	oct = counter;
	oct = oct << g_asm->shift;
	g_struct[i]->octet = g_struct[i]->octet | oct;
	if (counter == 1)
		handle_first_arg(arg, k, pre_matrix);
	else if (counter == 2)
		handle_second_arg(pre_matrix, i, arg, k);
	else if (counter == 3)
		handle_third_arg(pre_matrix, i, arg, k);
}
