/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reminder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharvey <hharvey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:59:58 by hharvey           #+#    #+#             */
/*   Updated: 2019/03/28 21:03:01 by hharvey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_reminder(int a, int b)
{
	int res;

	res = a % b;
	if (res < 0)
		return (res + b);
	return (res);
}
