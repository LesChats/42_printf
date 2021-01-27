/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nulladdrsprint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:40:17 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/27 16:57:45 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	uprint_null(t_prntf *p)
{
	if (p->flags & ZERO && !(p->flags & PRECIZ ))
	{
		p->preciz += p->width;
		p->width = 0;
	}
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
	buffer("0x", 2, 0);
	while (p->preciz > 0)
	{
		buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
		p->preciz -= 10;
	}
}

void	uprint_minnull(t_prntf *p)
{
	buffer("0x", 2, 0);
	while (p->preciz > 0)
	{
		buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
		p->preciz -= 10;
	}
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
}

