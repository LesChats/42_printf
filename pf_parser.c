/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 12:47:21 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 12:13:53 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//[flags][width][.precision][size]type
// l ll h hh

static inline void	parse_flags_width(t_prntf *p)
{
	while (1)
	{
		if (*p->format == '#')
			p->flags |= HASH;
		else if (*p->format == ' ')
			p->flags |= SPACE;
		else if (*p->format == '+')
			p->flags |= PLUS;
		else if (*p->format == '-')
			p->flags |= MINUS;
		else if (*p->format == '0')
			p->flags |= ZERO;
		else if (*p->format == '*')
			p->flags |= WILLCARD;
		else
			break ;
		++p->format;
	}
	if (ISNUM(*p->format))
		p->width = ft_atoii(&p->format);
	if (p->flags & WILLCARD)
		if ((p->width = (int)va_arg(p->ap, int)) < 0)
		{
			p->flags | MINUS;
			p->width = -p->width;
		}
	//priorite du + sur le blanc
	if (p->flags & PLUS)
		p->flags &= ~SPACE;
	// prio - sur 0
	if (p->flags & MINUS)
		p->flags &= ~ZERO;
}

static inline void	parse_preciz_type(t_prntf *p)
{
	if (*p->format == '.')
	{
		++p->format;
		p->flags |= PRECIZ;
		if (ISNUM(*p->format))
			p->preciz = ft_atoii(&p->format);
		if (*p->format == '*')
			if ((p->preciz = (int)va_arg(p->ap, int)) < 0)
				p->preciz = 0;
	}	
	if (*p->format == 'h')
	{
		++p->format;
		if (*p->format == 'h' && ++p->format)
			p->flags |= CHAR;
		else
			p->flags |= SHORT;
	}
	else if (*p->format == 'l')
	{
		++p->format;
		if (*p->format == 'l' && ++p->format)
			p->flags |= LLONG;
		else
			p->flags |= LONG;
	}
}

static void	pf_printlen(t_prntf *p)
{
		const int i = buffer("", 0, 0);
		printf("helloo iii = %d\n", i);

	        *va_arg(p->ap, int*) = i; 
}

static inline void	parse_type(t_prntf *p)
{
	const char c = *p->format++;
// cdefgipsuxnX
	if (c == 'c')
		pf_putchar(p);
	else if (c == 's')
		pf_putstr(p);
	else if (c == 'd' || c == 'i')
		pf_putnbr(p);
	else if (c == 'x' || c == 'X' || c == 'u')
		pf_unsigned(p, c);
	else if (c == 'p')
		pf_adresse(p);
	else if (c == 'f')
		pf_floats(p);
	else if (c == 'n')
		pf_printlen(p);
	else 
	{
		buffer("%", 1, 0);
		while (*p->format != '%')
			--p->format;
		++p->format;
	}
	/*
		pf_putnbr_exp(p);
	else if (c == 'g')
		;
		//pass
	*/
}

void	parse(t_prntf *p)
{
	p->flags = 0;
	p->width = 0;
	p->preciz = 0;
	parse_flags_width(p);
	parse_preciz_type(p);
	parse_type(p);
}

