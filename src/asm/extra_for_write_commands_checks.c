/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_for_write_commands_checks.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:00:06 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 13:36:48 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_if_command_exist(char *temp)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(temp, g_op_tab[i].name) == 1)
			return (1);
	}
	return (0);
}

int		check_if_label_exist(char *temp)
{
	int		i;

	i = -1;
	while (++i < INDEX)
	{
		if (ft_strequ(temp, g_struct[i]->label) == 1)
			return (0);
	}
	return (1);
}

void	check_labels_validity(char **temp)
{
	int	i;

	i = -1;
	if (!(check_if_label_exist(*temp)))
	{
		ft_strdel(temp);
		lexical_error();
	}
	while (temp[0][++i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, temp[0][i]) == 0)
		{
			g_asm->i = g_asm->i - ft_strlen(*temp) + i;
			ft_strdel(temp);
			lexical_error();
		}
	}
}

void	check_invalid_args_end_of_file(char **temp)
{
	int		i;
	int		counter;

	if (BUFFER[g_asm->i] == '\0')
	{
		ft_strdel(temp);
		ft_putstr("Syntax error - unexpected end of input ");
		close_with_error("(Perhaps you forgot to end with a newline ?)");
	}
	i = -1;
	counter = 0;
	while (temp[0][++i] != '\0')
	{
		if (temp[0][1] == ',')
			counter++;
		if (counter == 2)
			while (temp[0][i] != ' ' && temp[0][i] != '\t' &&
					temp[0][i] != '\0')
				i++;
	}
	if (temp[0][i] != COMMENT_CHAR && temp[0][i] != '\0')
	{
		ft_strdel(temp);
		syntax_error(5);
	}
}

void	check_invalid_number_of_args(char ***array, int i, int flag)
{
	if (flag == 1 && i < g_op_tab[g_struct[INDEX]->id_in_tab].var_count)
	{
		i = -1;
		if (array && *array)
		{
			while (array[0][++i] != NULL)
				free(array[0][i]);
			free(*array);
		}
		ft_putstr("Invalid parameter count for instruction ");
		close_with_error(g_struct[INDEX]->command);
	}
	if (flag == 2 && i > g_op_tab[g_struct[INDEX]->id_in_tab].var_count)
	{
		i = g_op_tab[g_struct[INDEX]->id_in_tab].var_count + 1;
		syntax_error_instruction(array[0][i - 1], find_flag(array[0][i - 1]));
	}
}
