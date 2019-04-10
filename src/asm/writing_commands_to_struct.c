/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_commands_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:35:56 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/10 13:35:31 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_label(char **temp)
{
	int		i;

	if (BUFFER[g_asm->i] == LABEL_CHAR)
	{
		check_labels_validity(temp);
		g_struct[INDEX]->label = ft_strdup(*temp);
		g_asm->i++;
		INDEX++;
		ft_strdel(temp);
		g_struct[INDEX]->str_number = g_asm->str_counter;
		return (1);
	}
	else if (BUFFER[g_asm->i] != LABEL_CHAR && ft_strlen(*temp) > 0)
	{
		i = g_asm->i;
		while (BUFFER[i] != '\n' && BUFFER[i] != '\0')
		{
			if (BUFFER[i] > 32)
				return (0);
			i++;
		}
		syntax_error(5);
	}
	return (0);
}

void	check_command(char **temp)
{
	if (BUFFER[g_asm->i] == ' ' || BUFFER[g_asm->i] == '\t' ||
	BUFFER[g_asm->i] == DIRECT_CHAR || BUFFER[g_asm->i] == LABEL_CHAR)
	{
		if (!(check_if_command_exist(*temp)))
			invalid_error_instruction(temp, 1);
		g_struct[INDEX]->command = ft_strdup(*temp);
		g_struct[INDEX]->id_in_tab = find_id_in_tab();
		if (g_op_tab[g_struct[INDEX]->id_in_tab].kod_tipov_argumenta == 1)
			g_struct[INDEX]->byte++;
		g_struct[INDEX]->byte++;
	}
	else if (BUFFER[g_asm->i] != ' ' && BUFFER[g_asm->i] != '\t' &&
													ft_strlen(*temp) > 0)
		syntax_error(5);
	ft_strdel(temp);
}

void	check_args(void)
{
	int		i;
	char	*temp;
	char	**array;

	temp = ft_strnew(count_args_size());
	i = -1;
	while (BUFFER[g_asm->i] != '\n' && BUFFER[g_asm->i] != '\0' &&
	BUFFER[g_asm->i] != COMMENT_CHAR)
		temp[++i] = BUFFER[g_asm->i++];
	check_invalid_args_end_of_file(&temp);
	array = split(temp);
	ft_strdel(&temp);
	i = 0;
	while (array[i] != NULL)
		i++;
	check_invalid_number_of_args(&array, i, 1);
	check_if_command_has_arg(array);
	check_invalid_number_of_args(&array, i, 2);
	i = -1;
	while (array[++i] != NULL)
	{
		g_struct[INDEX]->arg[i] = ft_strdup(array[i]);
		ft_strdel(&array[i]);
	}
	(array) ? free(array) : 0;
}

void	write_labels_commands(void)
{
	char	*temp;
	int		i;

	skip_comment_and_spaces();
	init_struct();
	while (BUFFER[g_asm->i] != '\0')
	{
		skip_comment_and_spaces();
		i = -1;
		temp = ft_strnew(count_chars());
		while (BUFFER[g_asm->i] != '\0' && BUFFER[g_asm->i] > 32 &&
		BUFFER[g_asm->i] != LABEL_CHAR && BUFFER[g_asm->i] != DIRECT_CHAR)
			temp[++i] = BUFFER[g_asm->i++];
		if (check_label(&temp) == 1)
			continue;
		check_command(&temp);
		skip_whitespaces();
		check_args();
		INDEX++;
		skip_whitespaces_com();
		(g_asm->buf[g_asm->i] == '\n') ? g_asm->str_counter++ : 0;
		g_struct[INDEX]->str_number = g_asm->str_counter;
		g_asm->i++;
		skip_comment_and_spaces();
	}
}
