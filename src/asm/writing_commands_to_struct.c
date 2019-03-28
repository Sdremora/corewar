/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_commands_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:35:56 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/28 19:29:25 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    check_valid_command_or_label(char **temp)
{
    int     i;
	int		n=0;
    i = -1;
    if (BUFFER[g_asm->i] == ' ')
    {
        // if (!(check_if_command_exist(*temp)))
        // {
        //     ft_strdel(temp);
        //     //Invalid instruction at token [TOKEN][008:001] INSTRUCTION "agnd"
        // }
		n = 0;//текущий индекс
		g_struct[n].command = ft_strdup(*temp);
        //write to g_struct->command from temp
    }
    else if (BUFFER[g_asm->i] == ':')
    {
        if (!(check_if_label_exist(*temp)))
        {
            ft_strdel(temp);
            //Invalid instruction at token [TOKEN][008:001] LABEL EXIST
        }
        g_struct[n].label = ft_strdup(*temp);
    }    
    else
		n = 0;
        //error Syntax error at token [TOKEN][008:004] ENDLINE
}

void    write_labels_commands(void)
{
    char    *temp;
	int		i;

	init_struct();
    while (BUFFER[g_asm->i] != '\0')
    {
        skip_comment_and_spaces();
        while (BUFFER[g_asm->i] != '\n')
        {
			i = -1;
            temp = ft_strnew(count_chars());
            while(BUFFER[g_asm->i] != ' ' || BUFFER[g_asm->i] != ':' ||
                                                    BUFFER[g_asm->i] != '\n')
				temp[++i] = BUFFER[g_asm->i++];
			check_valid_command_or_label(&temp);
			ft_strdel(&temp);
			g_asm->i++;
        }

		g_asm->i++;
    }
}