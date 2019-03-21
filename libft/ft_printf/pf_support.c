/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_support.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:04:17 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/06 13:45:02 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Для сокращения строк при проверках и обновлениях статуса ошибок
*/

int			set_status(int status)
{
	g_status = status;
	return (ERROR);
}

int			escape_initial(t_escape *escape)
{
	ft_bzero(escape->flags, F_DEF + 1);
	escape->width = 0;
	escape->precision = -1;
	escape->len_sp = LSP_DEF;
	escape->specifier = '\0';
	escape->str_len = 0;
	escape->prefix_len = 0;
	escape->postfix_len = 0;
	escape->str_simple = NULL;
	escape->str = NULL;
	escape->str_utf8 = NULL;
	escape->prefix = NULL;
	escape->postfix = NULL;
	escape->error_char = '\0';
	return (0);
}
