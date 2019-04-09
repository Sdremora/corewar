/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:58:59 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/09 16:55:37 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	if (flag == 4)
		ft_putstr("INSTRUCTION \"");
	else if (flag == 3)
		ft_putstr("INDIRECT \"");
	else if (flag == 2)
		ft_putstr("DIRECT \"");
	else if (flag == 1)
		ft_putstr("REGISTR \"");
	ft_putstr(instruction);
	ft_putstr("\"\n");
	del_all_struct();
	exit(0);
}
