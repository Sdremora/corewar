/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelsave.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:10:01 by hharvey           #+#    #+#             */
/*   Updated: 2019/03/25 20:21:28 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdelsave(t_list *src_lst, t_list *del_lst,
		void (*del)(void *, size_t))
{
	t_list *prev;
	t_list *next;
	t_list *lst;

	lst = src_lst;
	prev = 0;
	while (lst)
	{
		next = lst->next;
		if (lst == del_lst)
		{
			ft_lstdelone(&lst, del);
			if (!prev)
				return (next);
			prev->next = next;
			return (src_lst);
		}
		prev = lst;
		lst = next;
	}
	return (src_lst);
}
