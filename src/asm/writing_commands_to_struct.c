/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_commands_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:35:56 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/03 18:20:28 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_id_in_tab(void)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(g_struct[INDEX].command, g_op_tab[i].name) == 1)
			return (i);
	}
	return (-1);
}

int		check_label(char **temp)
{
    int     i;

    i = -1;
    if (BUFFER[g_asm->i] == LABEL_CHAR)
    {
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
        g_struct[INDEX].label = ft_strdup(*temp);
		g_asm->i++;
		printf("\n\nlabel: %s\n", g_struct[INDEX].label);
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
		printf("&&&&\n");
		syntax_error(5);
	}
    return (0);
}

void    check_command(char **temp)
{
    if (BUFFER[g_asm->i] == ' ' || BUFFER[g_asm->i] == '\t')
    {
		//printf("temp4: %s\n", *temp);
        if (!(check_if_command_exist(*temp)))
			invalid_error_instruction(temp, 1);
		//printf("temp5: %s\n", *temp);
		g_struct[INDEX].command = ft_strdup(temp[0]);
		g_struct[INDEX].id_in_tab = find_id_in_tab();
		if (g_op_tab[g_struct[INDEX].id_in_tab].kod_tipov_argumenta == 1)
			g_struct[INDEX].byte++;
		g_struct[INDEX].byte++;
        ft_strdel(temp);
		printf("command: %s\n", g_struct[INDEX].command);
		printf("id in tab = %d\n", g_struct[INDEX].id_in_tab);
    }
    else if (BUFFER[g_asm->i] != ' ' && BUFFER[g_asm->i] != '\t' && ft_strlen(*temp) > 0)
	{
		printf("__2___\n");
        syntax_error(5);
	}	
}        

void	check_args(void)
{
	int		i;
	char	*temp;
	char	**array;

	i = 0;
	skip_whitespaces();
	while (BUFFER[g_asm->i] != '\n' && BUFFER[g_asm->i] != '\0')
	{
		i++;
		g_asm->i++;
	}
	temp = ft_strnew(i);
	g_asm->i -= i;
	i = -1;
	while (BUFFER[g_asm->i] != '\n' && BUFFER[g_asm->i] != '\0')
		temp[++i] = BUFFER[g_asm->i++];
	if (BUFFER[g_asm->i] == '\0' && ft_strlen(temp) <= 0)
	{
		ft_strdel(&temp);
		return ;
	}	
	if (BUFFER[g_asm->i] == '\0')
	{
		ft_strdel(&temp);
		ft_putstr("Syntax error - unexpected end of input ");
		close_with_error("(Perhaps you forgot to end with a newline ?)");
	}
	array = split(temp, SEPARATOR_CHAR);
	ft_strdel(&temp);
	i = 0;
	while (array[i] != NULL)
		i++;
	if (i < g_op_tab[g_struct[INDEX].id_in_tab].var_count)
	{
		i = -1;
		if (array)
		{
			while(array[++i] != NULL)
				ft_strdel(&array[i]);
		}
		ft_putstr("Invalid parameter count for instruction ");
		close_with_error(g_struct[INDEX].command);
	}
	check_if_command_has_arg(array);
	if (i > g_op_tab[g_struct[INDEX].id_in_tab].var_count)
	{
		i = -1;
		if (array)
		{
			while(array[++i] != NULL)
				ft_strdel(&array[i]);
		}
		i = g_op_tab[g_struct[INDEX].id_in_tab].var_count + 1;
		syntax_error_instruction(array[i], find_flag(array[i]));
	}	
	i = -1;
	while (array[++i] != NULL)
	{
		g_struct[INDEX].arg[i] = array[i];
		//ft_strdel(&array[i]);
	}	
	if (array)
		free(array);
}

void    write_labels_commands(void)
{
    char    *temp;
	int		i;

	skip_comment_and_spaces();
	init_struct();
    while (BUFFER[g_asm->i] != '\0')
    {
        skip_comment_and_spaces();
		i = -1;
		temp = ft_strnew(count_chars());
		while(BUFFER[g_asm->i] != '\0' && BUFFER[g_asm->i] > 32 &&
		BUFFER[g_asm->i] != LABEL_CHAR && BUFFER[g_asm->i] != '\n')
			temp[++i] = BUFFER[g_asm->i++];
		if (check_label(&temp) == 1)
		{
			INDEX++;
			ft_strdel(&temp);
			continue;
		}
		check_command(&temp);
		skip_whitespaces();
		check_args();
		ft_strdel(&temp);
		INDEX++;
		if (g_asm->buf[g_asm->i] == '\n')
			g_asm->str_counter++;
		g_asm->i++;
		skip_comment_and_spaces();
    }
}