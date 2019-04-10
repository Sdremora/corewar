/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:47:29 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/10 12:00:04 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	for  finding position in in syntax errors we use flags:
**	1 - for COMMAND COMMENT
**	2 - for COMMAND NAME
**	3 - for STRING
**	5 - for ENDLINE
**	6 - for END
**	for printing error if champion name or comment length too long we have
**	function length error: 1 for name, 2 for comment
**	syntax_error_instruction(char *instruction, int flag)
**	1 - for INSTRUCTION
**	2 - for INDIRECT
**	3 - for DIRECT
**	4 - for REGISTR
*/

void	lexical_error(void)
{
	ft_putstr("Lexical error at [");
	ft_putnbr(g_asm->str_counter);
	ft_putchar(':');
	ft_putnbr(find_position_in_str());
	ft_putstr("]\n");
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
	ft_putstr(*instruction);
	ft_putstr("\"\n");
	ft_strdel(instruction);
	del_all_struct();
	exit(0);
}

void	error_no_label(char *label, int index)
{
	int		i;
	char	*temp;
	int		flag;

	flag = 0;
	ft_putstr("No such label ");
	ft_putstr(label);
	ft_putstr(" while attempting to dereference token [TOKEN][");
	print_noll(g_struct[index]->str_number);
	ft_putnbr(g_struct[index]->str_number);
	temp = ft_strjoin(":", label);
	i = find_label_index(temp, &flag);
	ft_putchar(':');
	if (BUFFER[flag + i - 2] == '%')
		i--;
	print_noll(i);
	ft_putnbr(i - 1);
	ft_putstr((BUFFER[flag + i - 1] == '%') ?
		"] DIRECT_LABEL \"%" : "] INDIRECT_LABEL \"");
	ft_putstr(temp);
	ft_putstr("\"\n");
	del_all_struct();
	exit(0);
}
