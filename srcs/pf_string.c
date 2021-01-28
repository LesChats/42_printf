/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 22:57:24 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/28 22:57:26 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	puterror(t_prntf *p)
{
	int len;

	len = 6;
	if ((p->flags & PRECIZ) && p->preciz < 6)
		len = p->preciz;
	if (p->width > len)
	{
		if (p->flags & MINUS)
		{
			buffer("(null)", len, 0);
			padding(p->width - len, p->flags & ZERO);
			return ;
		}
		padding(p->width - len, p->flags & ZERO);
	}
	buffer("(null)", len, 0);
}

static void	wstr_intobuffer(char *s, size_t size, t_prntf *p)
{
	if (p->flags & PRECIZ)
		size = (size > (size_t)p->preciz) ? (size_t)p->preciz : size;
	if (((size_t)p->width > size))
	{
		if (p->flags & MINUS)
		{
			buffer(s, size, 0);
			padding(p->width - size, 0);
		}
		else
		{
			padding(p->width - size, 0);
			buffer(s, size, 0);
		}
		free(s);
		return ;
	}
	buffer(s, size, 0);
	free(s);
}

static void	add_wchar(char *dest, unsigned size, unsigned c)
{
	char tmp[4];

	if (!size)
		return ;
	if (size == 1)
		tmp[0] = (char)c;
	else
	{
		if (size == 2)
			tmp[0] = (char)((c & (0x1f << 6)) >> 6) | 0xC0;
		else
		{
			if (size == 3)
				tmp[0] = (char)((c >> 12) & 0xf) | 0xE0;
			else
			{
				tmp[0] = (char)(((c >> 18) & 7) | 0xF0);
				tmp[1] = (char)(((c >> 12) & 0x3f) | 0x80);
			}
			tmp[size - 2] = (char)(((c >> 6) & 0x3f) | 0x80);
		}
		tmp[size - 1] = (char)((c & 0x3f) | 0x80);
	}
	ft_memcpy(dest, tmp, size);
}

static void	putwstr(t_prntf *p)
{
	t_string	str;
	wchar_t		*s;
	unsigned	tmp;

	if (!(s = va_arg(p->ap, wchar_t *)))
		return (puterror(p));
	initializ_string(&str);
	if (!(str.s))
		return ;
	while (*s)
	{
		tmp = wcharlen(*(unsigned *)s);
		if (tmp + str.idx > str.size)
		{
			str.save = str.s;
			str.size <<= 1;
			if (!(str.s = (char *)malloc(str.size)))
				return (free(str.save));
			ft_memcpy(str.s, str.save, str.idx);
			free(str.save);
		}
		add_wchar(str.s + str.idx, tmp, *(unsigned *)s++);
		str.idx += tmp;
	}
	return (wstr_intobuffer(str.s, str.idx, p));
}

void		pf_putstr(t_prntf *p)
{
	size_t		n;
	const char	*s;

	if (p->flags & LONG || p->flags & LLONG)
		return (putwstr(p));
	if (!(s = va_arg(p->ap, const char *)))
		return (puterror(p));
	n = ft_strlen(s);
	if (p->flags & PRECIZ)
		n = (n > (size_t)p->preciz) ? (size_t)p->preciz : n;
	if (((size_t)p->width > n))
	{
		if (p->flags & MINUS)
		{
			buffer(s, n, 0);
			return (padding(p->width - n, 0));
		}
		padding(p->width - n, 0);
	}
	buffer(s, n, 0);
}
