/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 05:04:40 by gcc               #+#    #+#             */
/*   Updated: 2020/12/17 12:42:07 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned	wcharlen(unsigned c)
{
	if (c < 0x80)
		return (1);
	else if (c < 0x800)
		return (2);
	else if (c < 0x10000)
		return (3);
	else if (c < 0xE0080)
		return (4);
	return (0);
}

static	void putwchar(const unsigned c, const unsigned size)
{
	char tmp[4];

	if (size == 1)
		tmp[0] = c;
	else
	{
		if (size == 2)
			tmp[0] = ((c & (0x1f << 6)) >> 6) | 0xC0;
		else
		{
			if (size == 3)
				tmp [0] = ((c >> 12 ) & 0xf) | 0xE0;
			else
			{
				tmp[0] = ((c >> 18) & 7) | 0xF0;
				tmp[1] = ((c >> 12) & 0x3f) | 0x80;
			}
			tmp[size - 2] = ((c >> 6) & 0x3f) | 0x80;
		}
		tmp[size - 1] = (c & 0x3f) | 0x80;
	}
	buffer(tmp, size, 0);
}

void	pf_putchar(t_prntf *p)
{
	const unsigned	c = va_arg(p->ap, unsigned);
	const unsigned	print = wcharlen(c);
	
	if (p->width > 0)
		--p->width;
	if (!(p->flags & MINUS))
	{
		while (p->width > 0)
		{
			buffer("          ", (p->width > 10 ) ? 10 : p->width, 0);
			p->width -= 10;
		}
		putwchar(c, print);
	}
	else
	{
		putwchar(c, print);
		while (p->width > 0)
		{
			buffer("          ", (p->width > 10 ) ? 10 : p->width, 0);
			p->width -= 10;
		}
	}
} 
