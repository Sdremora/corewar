/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:47:29 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/28 11:03:00 by mnarbert         ###   ########.fr       */
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
 **	6 - for END
 ** for printing error if champion name or comment length too long we have 
 ** function length error: 1 for name, 2 for comment

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
	ft_putstr("Syntax error at token [TOKEN][");
	print_noll(g_asm->str_counter);
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	i = find_position_in_str(buf);
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
	else if (flag == 5)
		ft_putstr("ENDLINE\n");
	else if (flag == 6)
		ft_putstr("END \"(null)\"\n");
	del_all_struct();
	exit(0);
}

void	length_error(int nb)
{
	if (nb == 1)
	{
		ft_putstr("Champion name too long (Max length ");
		ft_putnbr(PROG_NAME_LENGTH);
		ft_putstr(")\n");
	}
	else if (nb == 2)
	{
		ft_putstr("Champion comment too long (Max length ");
		ft_putnbr(COMMENT_LENGTH);
		ft_putstr(")\n");
	}
	del_all_struct();
	exit(0);
}