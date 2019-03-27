/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:08:27 by mnarbert          #+#    #+#             */
/*   Updated: 2019/03/26 17:59:12 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H

#include "general/op.h"
#include "libft.h"
#include <stdio.h>

# define HEADER		g_asm->matrix[0] 
# define NAME		g_asm->matrix[1] 
# define ZERO		g_asm->matrix[2] 
# define SIZE		g_asm->matrix[3] 
# define COMMENT	g_asm->matrix[4] 
# define CODE 		g_asm->matrix[5] 
/*struct g_asm is for different things:
**	binary_name saves the name of the final binary file
**	in matrix we will have 5 str for final binary code: 
**	matrix[0](HEADER) for magic header; matrix[1](NAME) for name of champion
**	matrix[2](ZERO) for NULL; matrix[3](SIZE) for code size
**	matrix[4](COMMENT) for comment; matrix[5](CODE) for code itself
**  str_count counts str in incomming file (we need it for ex. for error messages)
*/	

typedef struct s_asm
{
	char		*binary_name;
	char		**matrix;
	int			str_counter;

}				t_asm;


t_asm			*g_asm;

void    usage(void);
void	close_with_error(char *str);
void    init(void);

#endif