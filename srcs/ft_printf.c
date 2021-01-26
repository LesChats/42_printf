/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:29:29 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/26 23:24:21 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*shr_pf(const char *s)
{
	size_t		word;
	size_t		*sss;
	int			i;

	while ((size_t)s & 0b111)
		if (*s++ == '%')
			return (s - 1);
		else if (*(s - 1) == '\0')
			return (s - 1);
	sss = (size_t *)s;
	while (1)
	{
		word = *sss++;
		if (((word - LOMAGIC) & (~word) & HIMAGIC) ||
			(((word ^ PC) - LOMAGIC) & ~(word ^ PC) & HIMAGIC))
		{
			s = (char *)(sss - 1);
			i = -1;
			while (++i < 8)
				if (s[i] == '%' || !s[i])
					return (s + i);
		}
	}
}

int					ft_printf(const char *format, ...)
{
	t_prntf		pf;
	const char	*convertion;

	pf.format = format;
	va_start(pf.ap, format);
	while (*(convertion = shr_pf(pf.format)))
	{
		buffer(pf.format, convertion - pf.format, 0);
		pf.format = convertion + 1;
		if (*pf.format == '%')
		{
			buffer("%", 1, 0);
			++pf.format;
		}
		else
			parse(&pf);
	}
	return (buffer(pf.format, ft_strlen(pf.format), 1));
}

void				pf_printlen(t_prntf *p)
{
	const int i = buffer("", 0, 0);

	if (p->flags & LLONG)
		*va_arg(p->ap, long long int*) = i;
	else if (p->flags & LONG)
		*va_arg(p->ap, long*) = i;
	else if (p->flags & CHAR)
		*va_arg(p->ap, unsigned char*) = i;
	else if (p->flags & SHORT)
		*va_arg(p->ap, short*) = i;
	else
		*va_arg(p->ap, int*) = i;
}
