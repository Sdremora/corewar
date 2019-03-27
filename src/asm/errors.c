/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:47:29 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 18:35:34 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
 /*for  finding position in in syntax errors we use flags:
 ** 1 - for COMMAND COMMENT
 ** 2 - for COMMAND NAME
 ** 2 - for INDIRECT
 ** 3 - for STRING
 ** 4 - for INSTRUCTION
 ** 5 - for ENDLINE
 **
 */

int		find_position_in_str(char *buf)
{
	int		i;

	i = 0;
	if (buf[g_asm->i] == '\n')
	{
		g_asm->i--;
		i += 2;
	}
	while (buf[g_asm->i] != '\n' && g_asm->i != 0)
	{
		g_asm->i--;
		i++;
	}
	return (i);
}

void    lexical_error(char *buf)
{
    ft_putstr("Lexical error at [");
   	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	ft_putnbr(find_position_in_str(buf));
	putchar(']');
	del_all_struct();
	exit(0);
}

void	print_noll(int nb)
{
	if (nb < 10)
	{
		ft_putnbr(0);
		ft_putnbr(0);
	}
	else if (nb < 100)
		ft_putnbr(0);
}

void	syntax_error(int flag, char *buf)
{
	int		i;
	//printf("%d\n", g_asm->i);
	ft_putstr("Syntax error at token [TOKEN][");
	print_noll(g_asm->str_counter);
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	i = find_position_in_str(buf);
	//printf("i:%d\n", i);
	print_noll(i);
	ft_putnbr(i);
	ft_putstr("] ");
	if (flag == 1)
	{
		ft_putstr("COMMAND_COMMENT \".comment\"\n");
	}
	else if (flag == 2)
	{
		ft_putstr("COMMAND_NAME \".name\"\n");
	}
	else if(flag == 5)
		ft_putstr("ENDLINE\n");
	del_all_struct();
	exit(0);
}	