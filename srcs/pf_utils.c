/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:45:18 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/27 16:45:20 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	end_bffr(t_bffr *bffr)
{
	const int res = bffr->tlen;

	bffr->tlen = 0;
	write(1, bffr->bff, bffr->i);
	bffr->i = 0;
	return (res);
}

int			buffer(const char *str, size_t n, const char flush)
{
	static t_bffr	bffr;
	size_t			diff;

	if (n == 0)
	{
		if (flush)
			return (end_bffr(&bffr));
		return (bffr.tlen);
	}
	bffr.tlen += n;
	diff = BUFF_SZ - bffr.i;
	while (n > diff)
	{
		n -= diff;
		ft_memcpy(bffr.bff + bffr.i, str, diff);
		bffr.i = 0;
		write(1, bffr.bff, BUFF_SZ);
		str += diff;
		diff = BUFF_SZ;
	}
	ft_memcpy(bffr.bff + bffr.i, str, n);
	bffr.i += n;
	if (flush)
		return (end_bffr(&bffr));
	return (42);
}

void		padding(int pad, const int zero)
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

void		initializ_string(t_string *str)
{
	str->s = (char *)malloc(BUFF_SZ);
	str->idx = 0;
	str->size = BUFF_SZ;
}
