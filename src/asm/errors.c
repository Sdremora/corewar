/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkihn <kkihn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:47:29 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/01 16:18:01 by kkihn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
 /*for  finding position in in syntax errors we use flags:
 ** 1 - for COMMAND COMMENT
 ** 2 - for COMMAND NAME
 ** 3 - for STRING
 ** 5 - for ENDLINE
 **	6 - for END
 ** for printing error if champion name or comment length too long we have 
 ** function length error: 1 for name, 2 for comment
 **
 ** syntax_error_instruction(char *instruction, int flag)
 **	1 - for INSTRUCTION
 ** 2 - for INDIRECT
 ** 3 - for DIRECT
 ** 4 - for REGISTR
 */

int		find_position_in_str(void)
{
	int		i;

	i = 0;
	if (BUFFER[g_asm->i] == '\n' && g_asm->i != 0)
	{
		g_asm->i--;
		i += 2;
	}
	while (BUFFER[g_asm->i] != '\n' && g_asm->i != 0)
	{
		g_asm->i--;
		i++;
	}
	return (i);
}

int		find_position_in_str_for_instruction(char *instruction)
{
	int		i;
	int		counter;
	char	*temp;

	if (BUFFER[g_asm->i] == '\n' && g_asm->i != 0)
		g_asm->i--;
	while (g_asm->buf[g_asm->i] != '\n' && g_asm->i != 0)
		g_asm->i--;
	i = 0;
	g_asm->i++;
	counter = g_asm->i;
	while (BUFFER[g_asm->i] != '\n' && BUFFER[g_asm->i] != '\0')
	{
		i++;
		g_asm->i++;
	}	
	temp = ft_strnstr(&BUFFER[counter], instruction, i);
	counter = 0;
	while (temp[counter] != '\n' && temp[counter] != '\0')
		counter++;
	return(i - counter + 1);
}

void    lexical_error(void)
{
    ft_putstr("Lexical error at [");
   	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	ft_putnbr(find_position_in_str());
	ft_putstr("]\n");

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

void	syntax_error(int flag)
{
	int		i;
	ft_putstr("Syntax error at token [TOKEN][");
	print_noll(g_asm->str_counter);
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	i = find_position_in_str();
	print_noll(i);
	ft_putnbr(i);
	ft_putstr("] ");
	if (flag == 1)
	{
		ft_putstr("COMMAND_COMMENT \".comment\"\n");
	}
	else if (flag == 2)
		ft_putstr("COMMAND_NAME \".name\"\n");
	else if (flag == 5)
		ft_putstr("ENDLINE\n");
	else if (flag == 6)
		ft_putstr("END \"(null)\"\n");

	del_all_struct();
	exit(0);
}

void	syntax_error_instruction(char *instruction, int flag)
{
	int		i;
	ft_putstr("Syntax error at token [TOKEN][");
	print_noll(g_asm->str_counter);
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	i = find_position_in_str_for_instruction(instruction);
	print_noll(i);
	ft_putnbr(i);
	ft_putstr("] ");
	if (flag == 1)
		ft_putstr("INSTRUCTION \"");
	else if (flag == 2)
		ft_putstr("INDIRECT \"");
	else if (flag == 3)
		ft_putstr("DIRECT \"");
	else if (flag == 4)
		ft_putstr("REGISTR \"");
	ft_putstr(instruction);
	ft_putstr("\"\n");
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

void	invalid_error_instruction(char **instruction, int flag)
{
	int		i;
	ft_putstr("Invalid instruction at token [TOKEN][");
	print_noll(g_asm->str_counter);
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	i = find_position_in_str_for_instruction(*instruction);
	print_noll(i);
	ft_putnbr(i);
	ft_putstr("] ");
	if (flag == 1)
		ft_putstr("INSTRUCTION \"");
	else if (flag == 2)
		ft_putstr("LABEL \"");
	// else if (flag == 3)
	// 	ft_putstr("DIRECT \"");
	// else if (flag == 4)
	// 	ft_putstr("REGISTR \"");
	ft_putstr(*instruction);
	ft_putstr("\"\n");
	ft_strdel(instruction);
	del_all_struct();
	exit(0);
}