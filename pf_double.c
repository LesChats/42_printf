/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:54:25 by gcc               #+#    #+#             */
/*   Updated: 2020/12/17 18:58:41 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static double	ft_pow10(int pow)
{
	static double pow10[20];
	double	ans;

	pow10 = {
		1, 10, 100, 1000,
		10000, 100000, 1000000, 10000000, 100000000, 1000000000,
		10000000000, 100000000000, 1000000000000, 10000000000000,
		100000000000000, 1000000000000000, 10000000000000000,
		100000000000000000, 1000000000000000000, 10000000000000000000,
	};
	if (pow < 20)
		return (pow10[pow]);
	ans = 1;
	while (pow > 20)
	{
		ans *= 10;
		pow--;
	}
	return (ans * pow10[20]);
}

static void	itoa_doux(t_prntf *p, double n, float decimal)
{
	
// revoir faux sur bcp de pts
// maxim 16 significativ digit :think;
void	pf_double(t_prntf *p)
{
	double n;
	double decimal;

	n = (double)va_arg(p->ap, double);
	if (p->flags & ZERO)
	{
		p->preciz = p->wide;
//		p->wide = 0;
	}
	if (!(p->flags & PRECIZ))
		p->preciz = 7;
	if (n < 0)
	{
		p->flags |= ISNEG;
		n = -n;
	}
	decimal = (n - (long)n) * ft_pow10(p->preciz + 1);
	decimal = ((long)decimal % 10 > 4) ? decimal / 10 + 1 : decimal / 10;
}


