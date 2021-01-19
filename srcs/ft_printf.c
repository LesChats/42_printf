/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:01:00 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 17:38:43 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//%[flags][width][.precision][size]type

static	const char *shr_pf(const char *s)
{
	size_t		word;
	size_t		*sss;
	int		i;

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
				if (s[i] == '%')
					return (s + i);
				else if (!s[i])
					return (s + i);
		}
	}
}	

int	ft_printf(const char *format, ...)
{
	t_prntf	pf;
	const char *convertion;
	//does I realy need format to be in a stuct ?
	pf.format = format;
	va_start(pf.ap, format);
	//maybe change the shr function for index;
	while (*(convertion = shr_pf(pf.format)))
	{
		//handel some exeption after the %
		buffer(pf.format, convertion - pf.format, 0);
		pf.format = convertion + 1;
		//if (!*pf.format || (*pf.format == ' ' && (!pf.format[1]
		//|| (!pf.format[2] && pf.format[1] == 'h'))))
		//	return (buffer("", 0, 1));
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

