/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:58:25 by gcc               #+#    #+#             */
/*   Updated: 2020/12/17 16:50:48 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
static int end_bffr(t_bffr *bffr)
{
	const int res = bffr->tlen;

	bffr->tlen = 0;
	write(1, bffr->bff, bffr->i);
	bffr->i = 0;
	return (res);
}

int	buffer(const char *str, size_t n, const char flush)
{
	static t_bffr	bffr;
	int		diff;

	diff = BUFF_SZ - bffr.i;
	while (n > diff)
	{
		n -= diff;
		ft_memcpy(bffr.bff + bffr.i, str, diff);
		bffr.i = 0;
		bffr.tlen += BUFF_SZ;
		write(1, bffr.bff, BUFF_SZ);
		str += diff;
		diff = BUFF_SZ;
	}	
	ft_memcpy(bffr.bff + bffr.i, str, n);
	bffr.i += n;
	bffr.tlen += n;
	if (flush)
		return (end_bffr(&bffr));
	return (bffr.tlen);
}

void	signes(const size_t flags)
{
	if (flags & ISNEG)
		buffer("-", 1, 0);
	else if (flags & PLUS)
		buffer("+", 1, 0);
	else if (flags & SPACE)
		buffer(" ", 1, 0);
}

void    padding_signed(const size_t flags, int pad)
{
	const int pad_size = (pad > 10) ? 10 : pad;

	if (flags & ZERO)
	{
		signes(flags);
		while (pad > 0)
		{
			buffer("0000000000", pad_size, 0);
			pad -= pad_size;
		}
		return ;
	}
	while (pad > 0)
	{
		buffer("          ", pad_size, 0);
		pad -= pad_size;
	}
	signes(flags);
}

void	padding(int pad, const int zero)
{ 
	if (zero)
		while (pad > 0)
		{
			buffer("0000000000", (pad > 10) ? 10 : pad, 0);
			pad -= 10;
		}
	else
		while (pad > 0)
		{
			buffer("          ", (pad > 10) ? 10 : pad, 0);
			pad -= 10;
		}
}
