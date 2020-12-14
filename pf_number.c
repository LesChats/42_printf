/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:17:10 by gcc               #+#    #+#             */
/*   Updated: 2020/12/14 13:57:40 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int get_len (long long x, int ans)
{
	ans = 0;
	while (x >= 10000000000)
	{
		x /= 10;
		ans++;
	}
	if (x >= 1000000000)
		return (ans += 10);
	if (x >= 100000000)
		return (ans += 9);
	if (x >= 10000000)
		return (ans += 8);
	if (x >= 1000000)    
		return (ans += 7);
	if (x >= 100000)
		return (ans += 6);
	if (x >= 10000)
		return (ans += 5);
	if (x >= 1000)
		return (ans += 4);
	if (x >= 100)
		return (ans += 3);
	if (x >= 10)         
		return (ans += 2);
	return (ans += 1);
}

static void printf_nbr(long long n, size_t flags, int preciz, int len)
{	
	char			nb[25];
	const int		save_len = len;
	
	while (preciz > 0)
	{
		buffer("0000000000", preciz > 10 ? 10 : preciz, 0);
		preciz -= 10;
	}
	while (len--)
	{
		nb[len] = '0' + (n % 10);
		n /= 10;
	}
	buffer(nb, save_len, 0);
}

static void	itoa_pf(long long n, t_prntf *p)
{
	int		len;

	len = get_len(n, len);
	if (p->flags & PRECIZ)
	{
		p->preciz -= len;
		if (p->preciz > 0)
			p->width -= p->preciz;
	}
	if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	p->width -= len;
	if (p->width > 0)
	{
		if (p->flags & MINUS)
		{
			printf_nbr(n, p->flags, p->preciz, len);
			padding(p->width, (p->flags & ZERO));
			return ;
		}
		padding(p->width, (p->flags & ZERO));
	}
	printf_nbr(n, p->flags, p->preciz, len);
}

void	pf_putnbr(t_prntf *p)
{
	long long n;

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
		n = -n;
		p->flags &= ~PLUS;
		buffer("-", 1, 0);
		p->width--;
	}
	(p->flags & SPACE) ? buffer(" ", 1, 0) : 0;
	(p->flags & PLUS) ? buffer("+", 1, 0) : 0;
	itoa_pf(n, p);
}

//handel prez and width please :(`
