/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:58:25 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 15:32:46 by gcc              ###   ########.fr       */
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
	size_t		diff;

	if (n == 0)
	{	
		if (flush)
			return (end_bffr(&bffr));
		return (bffr.tlen);
	}
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
	return (42);
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

/*
int	add_cto_string(t_string *str, char c)
{
	if (str->idx == str->size)
	{
		str->save = str->s;
		str->size <<= 1;
		if (!(str->s = (char *)malloc(str->size)))
		{
			free(str->save);
			return (0);
		}
		ft_memcpy(str->s, str->save, str->idx);
		free(str->save);
	}
	str->s[str->idx++] = c;
}

static int	add_to_string(t_string *str, const char *src, unsigned len)
{
	while (str->idx + len > str->size)
	{
		str->save = str->s;
		str->size <<= 1;
		if (!(str->s = (char *)malloc(str->size)))
		{
			free(str->save);
			return (0);
		}
		ft_memcpy(str->s, str->save, str->idx);
		free(str->save);
	}
	ft_memcpy(str->s + str->idx, src, len);
	str->idx += len;
}

void		pf_atoi(t_string *str, uint64_t n)
{
	char	tmp[464];
	int	i;

	if (!n)
		add_to_string(str, "0", 1);
	else
	{
		i = 464;
		while (n)
		{
			tmp[--i] = '0' + (n % 10);
			n /= 10;
		}
		add_to_string(str, tmp + i, 464 - i);
	}
}	
*/
