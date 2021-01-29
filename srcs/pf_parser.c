/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 22:56:23 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/29 03:24:59 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				find_flags(const char **s, size_t *flags)
{
	while (1)
	{
		if ((unsigned)(**s) - ' ' > 16)
			return ;
		if (**s == '#')
			*flags |= HASH;
		else if (**s == ' ')
			*flags |= SPACE;
		else if (**s == '+')
			*flags |= PLUS;
		else if (**s == '-')
			*flags |= MINUS;
		else if (**s == '0')
			*flags |= ZERO;
		else if (**s == '*')
			*flags |= WILLCARD;
		else
			return ;
		(*s)++;
	}
}

static inline void		parse_flags_width(t_prntf *p)
{
	find_flags(&p->format, &p->flags);
	if (((unsigned)(*p->format) - '0') < 10)
		p->width = ft_atoii(&p->format);
	if (p->flags & WILLCARD)
		if ((p->width = (int)va_arg(p->ap, int)) < 0)
		{
			p->flags |= MINUS;
			p->width = -p->width;
		}
	find_flags(&p->format, &p->flags);
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
	if (!(p->flags & PRECIZ))
		p->preciz = 0;
	parse_type(p);
}
