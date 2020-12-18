/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:54:25 by gcc               #+#    #+#             */
/*   Updated: 2020/12/18 04:38:13 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	ft_pow10(int pow)
{
	static long pow10[18]  = {
		1, 10, 100, 1000,
		10000, 100000, 1000000, 10000000, 100000000, 1000000000,
		10000000000, 100000000000, 1000000000000, 10000000000000,
		100000000000000, 1000000000000000, 10000000000000000,
		100000000000000000
	};
	return (pow10[pow]);
}

static inline void deci_zero(char *tmp, int *idx)
{
	if (*idx == 48)
	{
		tmp[--*idx] = '0';
		tmp[--*idx] = '0';
		tmp[--*idx] = '0';
	}
	tmp[--*idx] = '.';
}

static void	itoa_doux(t_prntf *p, long n, long decimal)
{
	char	tmp[48];
	int	len;
	int	i;

	i = 48;
	while (decimal)
	{
		tmp[--i] = '0' + (decimal % 10);
		decimal /= 10;
	}
	deci_zero(tmp, &i);
	(!n) ? tmp[--i] = '0' : 0;
	while (n)
	{
		tmp[--i] = '0' + (n % 10);
		n /= 10;
	}
	len  = 48 - i;
	if ((p->preciz -= len) > 0)
		p->width -= p->preciz;
	p->width -= len;
	if (p->flags & MINUS)
		return (print_minus(p, tmp + i, len));
	if (p->flags & ZERO && (p->preciz = p->width))
		p->width = 0;
	print(p, tmp + i, len);
}

void	pf_double(t_prntf *p)
{
	double	n;
	long	decimal;
	int	decimal_size;

	n = (double)va_arg(p->ap, double);
	if (!(p->flags & PRECIZ))
		p->preciz = 6;
	//else
	//	p->flags &= ~ZERO;
	if (n < 0)
	{
		p->flags |= ISNEG;
		n = -n;
		--p->width;
	}
	decimal_size = (p->preciz > 16) ? 16 : p->preciz;
	p->preciz -= decimal_size;
	decimal = (n - (long)n) * ft_pow10(decimal_size + 1);
	if ((decimal % 10) > 4)
		decimal = decimal / 10 + 1;
	else
		decimal = decimal / 10;
//	decimal = (decimal % 10 > 4) ? decimal + 1 : decimal;
	itoa_doux(p, (long)n, decimal); 
}


