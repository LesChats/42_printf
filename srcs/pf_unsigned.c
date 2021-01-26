/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:29:28 by gcc               #+#    #+#             */
/*   Updated: 2021/01/27 00:33:24 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		uprint(t_prntf *p, const char *num, int len)
{
	p->width -= (p->flags & HASH) ? len + 2 : len;
	if (p->flags & ZERO && (p->preciz = p->width))
		p->width = 0;
	while (p->width > 0)
	{
		buffer("          ", (p->width > 10) ? 10 : p->width, 0);
		p->width -= 10;
	}
	if (p->flags & POINTER)
	{
		(p->flags & PLUS) ? buffer("+", 1, 0) : 0;
		(p->flags & SPACE) ? buffer(" ", 1, 0) : 0;
	}
	if (p->flags & HASH)
		(p->flags & UPPER) ? buffer("0X", 2, 0) : buffer("0x", 2, 0);
	while (p->preciz > 0)
	{
		buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
		p->preciz -= 10;
	}
	buffer(num, len, 0);
}

static void		uprint_min(t_prntf *p, const char *num, int len)
{
	p->width -= len;
	if (p->flags & POINTER)
	{
		(p->flags & PLUS) ? buffer("+", 1, 0) : 0;
		(p->flags & SPACE) ? buffer(" ", 1, 0) : 0;
	}
	if (p->flags & HASH)
	{
		p->width -= 2;
		if (p->flags & UPPER)
			buffer("0X", 2, 0);
		else
			buffer("0x", 2, 0);
	}
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

static void		itoa_base(t_prntf *p, unsigned long long n, int base)
{
	int			i;
	int			len;
	char *const	hex = (p->flags & UPPER) ? HEX_U : HEX_L;
	char		tmp[21];

	i = 21;
	if (!n)
		tmp[--i] = '0';
	while (n)
	{
		tmp[--i] = hex[n % base];
		n /= base;
	}
	len = 21 - i;
	if (p->flags & PRECIZ)
	{
		if (!p->preciz && tmp[i] == '0')
			len = 0;
		p->preciz -= len;
		if (p->preciz > 0)
			p->width -= p->preciz;
	}
	(p->flags & MINUS) ? uprint_min(p, tmp + i, len) : uprint(p, tmp + i, len);
}

void			pf_adresse(t_prntf *p)
{
	void *ptr;

	if (!(ptr = va_arg(p->ap, void *)))
	{
		p->preciz = 0;
		if (p->flags & MINUS)
			uprint_min(p, "(nil)", 5);
		else
			uprint(p, "(nil)", 5);
		return ;
	}
	p->flags |= HASH;
	p->flags |= POINTER;
	if (p->flags & PRECIZ)
		p->flags &= ~ZERO;
	if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	itoa_base(p, (unsigned long long)ptr, 16);
}

void			pf_unsigned(t_prntf *p, char c)
{
	unsigned long long n;

	if (c == 'X')
		p->flags |= UPPER;
	if (p->flags & PRECIZ)
		p->flags &= ~ZERO;
	if (p->flags & CHAR)
		n = (unsigned long long)((unsigned char)va_arg(p->ap, int));
	else if (p->flags & SHORT)
		n = (unsigned long long)((unsigned short)va_arg(p->ap, int));
	else if (p->flags & LONG)
		n = (unsigned long long)va_arg(p->ap, unsigned long);
	else if (p->flags & LLONG)
		n = va_arg(p->ap, unsigned long long);
	else
		n = (unsigned long long)va_arg(p->ap, unsigned int);
	if (c == 'u' || c == 'o')
	{
		p->flags &= ~HASH;
		(c == 'u') ? itoa_base(p, n, 10) : itoa_base(p, n, 8);
		return ;
	}
	if (!n)
		p->flags &= ~HASH;
	itoa_base(p, n, 16);
}
