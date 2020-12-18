/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:54:25 by gcc               #+#    #+#             */
/*   Updated: 2020/12/17 17:11:30 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_double(t_prntf *p)
{
	double n;

	n = (double)va_arg(p->ap, double);
	if (p->flags & ZERO)
	{
		p->preciz = p->wide;
		p->wide = 0;
	}
	if (!(p->flags & PRECIZ))
		p->preciz = 7;
	if (n < 0)
	{
		p->flags |= ISNEG;
	
