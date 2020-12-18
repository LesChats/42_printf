/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_signed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:17:10 by gcc               #+#    #+#             */
/*   Updated: 2020/12/18 03:40:27 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print(t_prntf *p, const char *num, int len)
{
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	while (p->preciz > 0)
	{
		buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
		p->preciz -= 10;
	}
	buffer(num, len, 0);
}

void print_minus(t_prntf *p, const char *num, int len)
{
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	while (p->preciz > 0)
	{
		buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
		p->preciz -= 10;
	}
	buffer(num, len, 0);
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
}

static void	itoa_pf(unsigned long long n, t_prntf *p)
{
	int		i;
	int		len;
	char		tmp [21];

	i = 21;
	if (!n) 
		tmp[--i] = '0';
	while (n)
	{
		tmp[--i] = '0' + (n % 10);
		n /= 10;
	}
	len = 21 - i;
	if (p->flags & PRECIZ)
	{
		p->preciz -= len;
		if (p->preciz > 0)
			p->width -= p->preciz;
	}
	p->width -= len;
	if (p->flags & MINUS)
		return(print_minus(p, tmp + i, len));
	if (p->flags & ZERO && (p->preciz = p->width))
		p->width = 0;
	print(p, tmp + i, len);
}

void	pf_putnbr(t_prntf *p)
{
	long long n;
	unsigned long long nn;

	if (p->flags & PRECIZ)
		p->flags &= ~ZERO; 
	if (p->flags & CHAR)
		n = (long long)((char)va_arg(p->ap, int));
	else if (p->flags & SHORT)
		n = (long long)((short)va_arg(p->ap, int));
	else if (p->flags & LONG)
		n = (long long)va_arg(p->ap, long);
	else if (p->flags & LLONG)
		n = va_arg(p->ap, long long);
	else
		n = (long long)va_arg(p->ap, int);
	if (n < 0)
	{
		nn = n * -1;
		p->flags |= ISNEG;
		--p->width;
	}
	else
		nn = n;
	if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	itoa_pf(nn, p);
}
