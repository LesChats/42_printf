/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:01:00 by gcc               #+#    #+#             */
/*   Updated: 2020/12/14 12:53:53 by gcc              ###   ########.fr       */
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
	t_prntf	p;
	// adress or index ?
	const char *convertion;
	//does I nedd to initialize all pf to 0 ?
	//yes => bzero

	//does I realy need format to be in a stuct ?
	p.format = format;
	va_start(p.ap, format);
	while (*(convertion = shr_pf(p.format)))
	{
		//printf("\non a trouver un %c\n\n\n", *convertion);
		//handel some exeption after the %
		buffer(p.format, convertion - p.format, 0);
		p.format = convertion + 1;
		//printf("\n format is = %c\n", *p.format);
		if (*p.format == '%')
		{
			buffer("%", 1, 0);
			++p.format;
		}
		else
			parse(&p);
		//somthing like that
		//	buf_add(&p, p.format, convertion - p.format);
		// 		p.format = convertion + 1;
	}
	return (buffer(p.format, ft_strlen(p.format), 1));
}

