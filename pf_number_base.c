/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_number_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 07:02:51 by gcc               #+#    #+#             */
/*   Updated: 2020/12/14 12:34:47 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void printf_unbr(unsigned long long n, size_t flags, int preciz, int len)
{
	char                    nb[25];
	const int		save_len = len;

	while (preciz > 0)
	{
		buffer("0000000000", preciz > 10 ? 10 : preciz, 0);
		preciz -= 10;
	}
	//if (!n)
	//	*--nb = '0';
	while (len--)
	{
		nb[len] = '0' + (n % 10);
		n /= 10;
	}
	buffer(nb, save_len, 0);
}

static void     itoa_upf(unsigned long long n, t_prntf *p)
{
	int	len;

	len = get_len(n, len);
	if (p->flags & PRECIZ)
	{
		p->preciz -= len;
		if (p->preciz > 0)
			p->width -= p->preciz;
	}
	p->width -= len;
	if (p->width > 0)
	{
		if (p->flags & MINUS)
		{
			printf_unbr(n, p->flags, p->preciz, len);
			padding(p->width, (p->flags & ZERO));
			return ;
		}
		padding(p->width, (p->flags & ZERO));
	}
	printf_unbr(n, p->flags, p->preciz, len);
}

//just for run... need to be re_f
void	printf_hex(unsigned long long n, size_t flags, int preciz, int len)
{
	char * const	hex_l = "0123456789abcdef";
	char * const	hex_u = "0123456789ABCDEF";
	char *		hex;
	char		tmp[25];
	const int	save_len = len;
	int		i;

	hex = (flags & UPPER) ? hex_u : hex_l;
	i = 0;
	if (flags & HASH)
	{
		tmp[0] = '0';
		tmp[1] = (flags & UPPER) ? 'X' : 'x'; 
		i = 2;
	}
	while (preciz > 0)
	{
		buffer("0000000000", preciz > 10 ? 10 : preciz, 0);
		preciz -= 10;
	}
	while (len--)
	{
		tmp[i + len] = hex[n % 16];
		n /= 16;
	}
	buffer(tmp, save_len + i, 0);
}

static void     itoa_hexpf(unsigned long long n, t_prntf *p)
{
	int			len;
	const unsigned long long save_n = n;

	len = 1;
	while ((n /= 16))
		++len;
	if (p->flags & PRECIZ)
	{
		p->preciz -= len;
		if (p->preciz > 0)
			p->width -= p->preciz;
	}
	if (p->flags & HASH)
		p->width -= 2;
	p->width -= len;
	if (p->width > 0)
	{
		if (p->flags & MINUS)
		{
			printf_hex(save_n, p->flags, p->preciz, len);
			padding(p->width, (p->flags & ZERO));
			return ;
		}
		padding(p->width, (p->flags & ZERO));
	}
	printf_hex(save_n, p->flags, p->preciz, len);
}

void    pf_puthex(t_prntf *p, char c)
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
	if (c == 'u')
		return (itoa_upf(n, p));
	itoa_hexpf(n, p);
}
