/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:52:31 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/02 13:31:04 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**here we init elements in g_asm and matrix elements. For all ellements except
** CODE we know its size. For CODE we take constant len = 500, then later we
** can remalloc it
*/

static void		fill_with_zerro(char *str, int len)
{
	int		i;
	
	i = -1;
	while (++i < len)
		str[i] = '0';
}

static void		init_matrix_element(char **element, int len)
{
	if (!(*element = ft_strnew(len)))
		close_with_error("Error by malloc\n");
	fill_with_zerro(*element, len);
}

void		init_matrix()
{
	char	*temp;
	if (!(g_asm->matrix = (char**)malloc(sizeof(char*) * 6)))
		close_with_error("Error by malloc\n");
	if (!(temp = ft_itoa_unsize_base(COREWAR_EXEC_MAGIC, 16)))
		close_with_error("Error by malloc\n");
	HEADER = ft_strjoin("00", temp);
	ft_strdel(&temp);
	init_matrix_element(&NAME, PROG_NAME_LENGTH / 2);
	init_matrix_element(&ZERO, 8);
	init_matrix_element(&SIZE, 8);
	init_matrix_element(&COMMENT, COMMENT_LENGTH / 2);
	init_matrix_element(&CODE, 500);
	//printf("header:%s\n\n\n name:%s\n\n\n, zero:%s\n\n\n size:%s\n\n\n comment:%s\n\n\n, code:%s\n\n\n", HEADER, NAME, ZERO, SIZE, COMMENT, CODE);
}

void		init(void)
{
	if (!(g_asm = (t_asm*)malloc(sizeof(t_asm))))
		close_with_error("Error by malloc");
    g_asm->binary_name = NULL;
	g_asm->str_counter = 1;
	g_asm->flag_name = -1;
	g_asm->flag_comment = -1;
	g_asm->index = 0;
	init_matrix();
}

int			count_all_str(void)
{
	int		i;
	int		counter;

	i = g_asm->i;
	counter = 1;
	while(BUFFER[i] != '\0')
	{
		if (BUFFER[i] == '\n')
			counter++;
		i++;
	}
	return(counter);
}

void		init_struct(void)
{
	int		i;
	int		counter;

	i = -1;
	counter = count_all_str();
	if (!(g_struct = (t_parse*)malloc(sizeof(t_parse) * counter)))
		close_with_error("Error by malloc");
	while(++i < counter)
	{
		g_struct[i].label = NULL;
		g_struct[i].command = NULL;
		g_struct[i].arg1 = NULL;
		g_struct[i].arg2 = NULL;
		g_struct[i].arg3 = NULL;
		g_struct[i].str_number = 0;
		g_struct[i].id_in_tab = -1;
		g_struct[i].byte = 0;
		g_struct[i].octet = 0;
	}
}
