/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_notfound.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:39:56 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 18:16:15 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void quick_atoi(int n)
{
	char	tmp[10];
	int	i;

	i = 10;
	if (n > 999999999)
		return ;
	if (!n)
		buffer("0", 1, 0);
	else
	{
		while (n)
		{
			tmp[--i] = '0' + (n % 10);
			n /= 10;
		}
		buffer(tmp + i, 10 - i, 0);
	}
}
void	pf_notfound(t_prntf *p)
{
	if (*p->format)
		buffer("%", 1, 0);
	else
		return ;
	if (*p->format == '%')
	{
		++p->format;
		return ;
	}
	if (p->flags & HASH)
		buffer("#", 1, 0);
	if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->flags & MINUS)
		buffer("-", 1, 0);
	else if (p->flags & ZERO)
		buffer("0", 1, 0);
	if (p->width)
		quick_atoi(p->width);
	if (p->flags & PRECIZ)
	{
		if (!(p->flags & WILLCARD))
			buffer(".", 1, 0);
		quick_atoi(p->preciz);
	}
}




