/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 12:47:21 by gcc               #+#    #+#             */
/*   Updated: 2021/01/26 23:57:07 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t			find_flags(char c)
{
	if (c == '#')
		return (HASH);
	else if (c == ' ')
		return (SPACE);
	else if (c == '+')
		return (PLUS);
	else if (c == '-')
		return (MINUS);
	else if (c == '0')
		return (ZERO);
	else if (c == '*')
		return (WILLCARD);
	return (0);
}

static inline void		parse_flags_width(t_prntf *p)
{
	size_t tmp;

	while ((tmp = find_flags(*p->format)))
	{
		p->flags |= tmp;
		++p->format;
	}
	if (((unsigned)(*p->format) - '0') < 10)
		p->width = ft_atoii(&p->format);
	if (p->flags & WILLCARD)
		if ((p->width = (int)va_arg(p->ap, int)) < 0)
		{
			p->flags |= MINUS;
			p->width = -p->width;
		}
	if (p->flags & PLUS)
		p->flags &= ~SPACE;
	if (p->flags & MINUS)
		p->flags &= ~ZERO;
}

static inline void		parse_preciz_type(t_prntf *p)
{
	if (*p->format == '.')
	{
		++p->format;
		p->flags |= PRECIZ;
		if (((unsigned)(*p->format) - '0') < 10)
			p->preciz = ft_atoii(&p->format);
		if (*p->format == '*')
		{
			++p->format;
			if ((p->preciz = (int)va_arg(p->ap, int)) < 0)
				p->flags &= ~PRECIZ;
		}
	}
	if (*p->format == 'h')
	{
		++p->format;
		p->flags |= (*p->format == 'h' && ++p->format) ? CHAR : SHORT;
	}
	else if (*p->format == 'l')
	{
		++p->format;
		p->flags |= (*p->format == 'l' && ++p->format) ? LLONG : LONG;
	}
}

static inline void		parse_type(t_prntf *p)
{
	const char c = *p->format++;

	if (c == 'c')
		pf_putchar(p);
	else if (c == 's')
		pf_putstr(p);
	else if (c == 'd' || c == 'i')
		pf_putnbr(p);
	else if (c == 'x' || c == 'X' || c == 'u' || c == 'o')
		pf_unsigned(p, c);
	else if (c == 'p')
		pf_adresse(p);
	else if (c == 'f')
		pf_floats(p);
	else if (c == 'e')
		pf_exponent(p);
	else if (c == 'g')
		pf_gishard(p);
	else if (c == 'n')
		pf_printlen(p);
	else
	{
		--p->format;
		pf_notfound(p);
	}
}

void					parse(t_prntf *p)
{
	p->flags = 0;
	p->width = 0;
	p->preciz = 0;
	parse_flags_width(p);
	parse_preciz_type(p);
	parse_type(p);
}
