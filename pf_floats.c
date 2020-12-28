/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 08:14:37 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 11:07:52 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void print(t_prntf *p, const char * num, char *dec, int len)
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
	buffer(num, len, 0);
	if (p->preciz)
		buffer(dec, p->preciz, 0);
	free(dec);
}

static void print_minus(t_prntf *p, const char *num, char *dec, int len) 
{
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	buffer(num, len, 0);
	if (p->preciz)
		buffer(dec, p->preciz, 0);
	free(dec);
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
}

static void	error_buff(t_prntf *p, const char *s, int n)
{
	char *empty;

	p->preciz = 0;
	if (!(empty = (char *)malloc(0)));
	return ;
	if (p->flags & MINUS)
		print_minus(p, s, empty, 3);
	else
		print(p, s, empty, 3);
}

static void	itoa_float(t_prntf *p, unsigned long long n, char *dec)
{
	char tmp[21];
	int i;
	int len;
	i = 21;
	if (p->preciz)
	{
		tmp[--i] = '.';
		p->width -= p->preciz;
	}
	(!n) ? tmp[--i] = '0' : 0;
	while (n)
	{
		tmp[--i] = '0' + (n % 10);
		n /= 10;
	}
	len = 21 - i;
	p->width -= len;
	if (p->flags & MINUS)
		return (print_minus(p, tmp + i, dec, len));
	print(p, tmp + i, dec, len);
}


void	pf_floats(t_prntf *p)
{
	long double		n;
	char			*dec;
	unsigned long long	integral_part;

	if (!(p->flags & PRECIZ))
		p->preciz = 6; 
	n = (long double)va_arg(p->ap, double);
	if (n != n)
		return (error_buff(p, "NaN", 3));
	if (n < 0)
	{
		p->flags |= ISNEG;
		n = 0.0 - n;
		--p->width;
	}
	else if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	if (n > DBL_MAX)
		return (error_buff(p, "inf", 3));
	integral_part = (unsigned long long)n;
	printf("int part = %lld\n", integral_part);
	if (!(dec = (char *)malloc(p->preciz)))
		return ;
	if (fill_decimals(dec, n - (double)integral_part, p->preciz))
		++integral_part;
	itoa_float(p, integral_part, dec);
}
