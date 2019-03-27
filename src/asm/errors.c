/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:47:29 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/27 13:22:02 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
 /*for  finding position in in syntax errors we use flags:
 ** 1 - for COMMAND NAME
 ** 2 - for INDIRECT
 ** 3 - for STRING
 ** 4 - for INSTRUCTION
 ** 5 - for ENDLINE
 **
 */
// void    lexical_error(int   nb)
// {
// 	ft_putstr("Lexical error at [");
// 	ft_putnbr(g_asm->str_counter);
// 	ft_putnbr(nb);
// 	del_all_struct();
// 	exit(0);
// }

// void    syntax_error(int   nb, char *str)
// {
//     ft_putstr("Syntax error at token [TOKEN][");
//     if (g_asm->str_counter < 10)
//     {
//         ft_putnbr(0);
//         ft_putnbr(0);
// 	}
// 	else if (g_asm->str_counter < 100)
// 		ft_putnbr(0);
// 	ft_putnbr(g_asm->str_counter);
// 	ft_putchar(':');
// 	if (nb < 10)
//     {
//         ft_putnbr(0);
//         ft_putnbr(0);
// 	}
// 	else if (nb < 100)
// 		ft_putnbr(0);
// 	ft_putnbr(nb);
// 	ft_putstr(str);
// 	del_all_struct();
// 	exit(0);
// }

// void	find_position_error_lex_name_comment(char **line)
// {
// 	int		i;

// 	i = 0;
// 	while (*line[i] == ' ' || *line[i] == '\t')
// 		i++;
// 	while (*line[i] != ' ' || *line[i] != '\t')
// 		i++;
// 	while (*line[i] == ' ' || *line[i] == '\t')
// 		i++;
// 	ft_strdel(line);
// 	lexical_error(i);
// }