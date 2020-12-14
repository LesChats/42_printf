/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:34:29 by gcc               #+#    #+#             */
/*   Updated: 2020/12/14 09:01:18 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	puterror(t_prntf *p)
{
	if ((p->flags & PRECIZ) & p->preciz > 5)
		buffer("(null)", 6, 0);
}

static void	wstr_intobuffer(char *s, size_t size, t_prntf *p)
{

	if (p->flags & PRECIZ)
		size = (size > p->preciz) ? p->preciz : size;
	if ((p->width > size))
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
	free(s);
	buffer(s, size, 0);
}

static char	*get_wchar(unsigned size, wchar_t c)
{
	char *tmp;
	if (!(tmp = (char *)malloc(size)))
		return (0);
	if (size == 1)
		tmp[0] = (char)c;
	else
	{
		if (size == 2)
			tmp[0] = (char)((c & (0x1f << 6)) >> 6) | 0xC0;
		else
		{
			if (size == 3)
				tmp [0] = (char)((c >> 12 ) & 0xf) | 0xE0;
			else
			{
				tmp[0] = (char)((c >> 18) & 7) | 0xF0;
				tmp[1] = (char)((c >> 12) & 0x3f) | 0x80;
			}
			tmp[size - 2] = (char)((c >> 6) & 0x3f) | 0x80;
		}
		tmp[size - 1] = (char)(c & 0x3f) | 0x80;
	}
	return (tmp);
}

static void	putwstr(t_prntf *p)
{
	t_string	str;
	wchar_t		*s;
	unsigned	tmp; 

	if (!(s = va_arg(p->ap, wchar_t *)))	
		return (puterror(p));
	if (!(str.s = (char *)malloc((str.size = BUFF_SZ) + 1)))
		return ;
	str.idx = 0;
	while (*s)
	{
		tmp = wcharlen(*s);
		if (tmp + str.idx > str.size)
		{
			str.save = str.s;
			str.size <<= 1;
			if (!(str.s = (char *)malloc(str.size)))
				return (free(str.save));
			ft_memcpy(str.s, str.save, str.idx);
			free(str.save);
		}
		ft_memcpy(str.s + str.idx, (str.save = get_wchar(tmp, *s++)), tmp);
		str.idx += tmp;
		free(str.save);
	}
	return (wstr_intobuffer(str.s, str.idx, p));
}


void	pf_putstr(t_prntf *p)
{
	size_t		n;
	const char	*s;

	if (p->flags & LONG || p->flags & LLONG)
		return (putwstr(p));
	if (!(s = va_arg(p->ap, const char *)))
		return (puterror(p));
			n = ft_strlen(s);
	if (p->flags & PRECIZ)
		n = (n > p->preciz) ? p->preciz : n;
	if ((p->width > n))
	{
		if (p->flags & MINUS)
		{
			buffer(s, n, 0);
			padding(p->width - n, 0);
		}
		else
		{
			padding(p->width - n, 0);
			buffer(s, n, 0);
		}
		return ;
	}
	buffer(s, n, 0);
}
