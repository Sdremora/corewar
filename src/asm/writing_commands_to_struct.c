/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_commands_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:35:56 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/01 12:23:03 by kkihn            ###   ########.fr       */
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
            close_with_error("Invalid instruction at token [TOKEN][008:001] LABEL EXIST");
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
		// printf("\n\nlabel: %s\n", g_struct[INDEX].label);
        return (1);
    }    
    else if (BUFFER[g_asm->i] == '\n')
        close_with_error("error Syntax error at token [TOKEN][008:004] ENDLINE");
    return (0);
}

void    check_command(char **temp)
{
    if (BUFFER[g_asm->i] == ' ')
    {
		//printf("temp4: %s\n", *temp);
        if (!(check_if_command_exist(*temp)))
        {
            ft_strdel(temp);
            close_with_error("Invalid instruction at token [TOKEN][008:001] INSTRUCTION \"agnd\"");
        }
		//printf("temp5: %s\n", *temp);
		g_struct[INDEX].command = ft_strdup(temp[0]);
		g_struct[INDEX].id_in_tab = find_id_in_tab();
        ft_strdel(temp);
		// printf("command: %s\n", g_struct[INDEX].command);
		// printf("id in tab = %d\n", g_struct[INDEX].id_in_tab);
    }
    else if (BUFFER[g_asm->i] == '\n')
         close_with_error("error Syntax error at token [TOKEN][008:004] ENDLINE");
}        

void	check_args(void)
{
	int		i;
	char	*temp;
	char	**array;

	i = 0;
	skip_whitespaces();
	while (BUFFER[g_asm->i] != '\n')
	{
		i++;
		g_asm->i++;
	}	
	temp = ft_strnew(i);
	g_asm->i -= i;
	i = -1;
	while (BUFFER[g_asm->i] != '\n')
		temp[++i] = BUFFER[g_asm->i++];
	array = split(temp, SEPARATOR_CHAR);
	if (!(check_if_command_has_arg(array)))
	{
		//free(array);
		 close_with_error("Syntax error at token [TOKEN][007:015] INDIRECT \"6\"");
	}
	i = -1;
	// while (array[++i] != NULL)
	// 	printf("arg: %s\n", array[i]);
	// printf("\n");
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
		while(BUFFER[g_asm->i] != ' ' && BUFFER[g_asm->i] != LABEL_CHAR &&
											BUFFER[g_asm->i] != '\n')
			temp[++i] = BUFFER[g_asm->i++];
		if (check_label(&temp) == 1)
		{
			INDEX++;
			ft_strdel(&temp);
			continue;
		}
		check_command(&temp);
		check_args();
		ft_strdel(&temp);
		INDEX++;
		g_asm->i++;
    }
}