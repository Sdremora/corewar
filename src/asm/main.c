/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:54:49 by mnarbert          #+#    #+#             */
/*   Updated: 2019/04/05 15:33:57 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_binary_name(char *str)
{
	int		len;
	int		i;
	
	len = ft_strlen(str);
	i = -1;
	if (str[len - 1] != 's' || str[len - 2] != '.')
		close_with_error("Can't read source file\n");
	while (len != 0 && str[len - 1] != '/')
		len--;
	if (!(g_asm->binary_name = ft_strnew(ft_strlen(str) - len - 1 + 3)))
		close_with_error("Error by malloc\n");
	if (str[len] == '/')
		len++;
	while (str[len] != '.')
		g_asm->binary_name[++i] = str[len++];
	g_asm->binary_name[++i] = '.';
	g_asm->binary_name[++i] = 'c';
	g_asm->binary_name[++i] = 'o';
	g_asm->binary_name[++i] = 'r';
	g_asm->binary_name[++i] = '\0';
}

int		count_code_size(void)
{
	int		i;
	int		j;
	int		counter;
	char	*temp;

	i = -1;
	counter = 0;
	while (++i < INDEX)
		counter += g_struct[i].byte;
	temp = ft_itoa_base(counter, 16, 1);
	i = ft_strlen(temp);
	j = 7;
	while(--i >= 0)
		SIZE[j--] = temp[i];
	ft_strdel(&temp);
	// printf("counter: %d, size:%s\n", counter, SIZE);
	return(counter * 2);
}

int		main(int argc, char **argv)
{
	int		i;

	i = -1;
	if (argc > 1)
	{
		init();
		write_binary_name(argv[argc - 1]);
		parse_from_file(argc, argv);
		// while (++i < INDEX)
		// {
		// 	printf("# of index: %d\n", i);
		// 	printf("label: %s, name:%s, byte:%d\n", g_struct[i].label, g_struct[i].command, g_struct[i].byte);
		// 	printf("arg1: %s, arg2: %s, arg3: %s\n\n", g_struct[i].arg[0], g_struct[i].arg[1], g_struct[i].arg[2]);
		// }
		g_asm->i = 0;
		count_code_size();
		init_matrix_element(&CODE, count_code_size());
		realise_algorithm();
		// printf("%s\n\n%s\n\n%s\n\n%s\n\n%s\n\n%s\n",HEADER,NAME,ZERO1,COMMENT,ZERO2,CODE);
		
		if (argc == 3 && ft_strequ(argv[1], "-hex") == 1)
			print_hexdump();
		make_binary();
		del_all_struct();
		// int i = 5;
		// write (1, &i, 4);
	}
	else
		usage();
	return (0);
}