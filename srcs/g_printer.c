/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:07:14 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/25 19:16:25 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

void printge(t_prntf *p, char *res, int16_t expon, t_tuple info)
{
	p->width -= (info.index + 5 + p->preciz); 
	if (info.index || p->preciz > 0 || (p->flags & HASH && p->flags & PRECIZ))
		p->width--;
	if (p->preciz == -1)
		p->width--;
	else if (info.pts && info.index)
		p->width++;
	if (!(p->flags & ZERO))
		fill_space("          ", p->width);
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->flags & ZERO)
		fill_space("0000000000", p->width);
	if (p->preciz ==  -1 && info.pts)
		buffer("1", 1, 0);
	buffer_exp(res, expon, info, p->preciz);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0 && p->flags & HASH)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
}

void print_minusge(t_prntf *p, char *res, int16_t expon, t_tuple info)
{
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz ==  -1 && info.pts)
		buffer("1", 1, 0);
	if (p->preciz == -1)
		p->width--;
	else if (info.pts && info.index)
		p->width++;
	buffer_exp(res, expon, info, p->preciz);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0 && p->flags & HASH)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
	p->width -= info.index + 5 + p->preciz;
	if (info.index || p->preciz > 0 || (p->flags & HASH && p->flags & PRECIZ))
		p->width--;
	fill_space("          ", p->width);
}

void printgf(t_prntf *p, char *res, t_tuple inf)
{
	p->width -= (inf.pts + inf.index) + ((p->preciz > 0) ? p->preciz + 1 : 0);
	p->width -= (p->preciz == -1);
	if (p->flags & HASH & p->flags & PRECIZ )
		--p->width;
	if (!(p->flags & ZERO))
		fill_space("          ", p->width);
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->flags & ZERO)
		fill_space("0000000000", p->width);
	if (p->preciz == -1)
		buffer("1", 1, 0);
	buffer(res, inf.pts + inf.index, 0);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0 && p->flags & HASH)
	{
		if (!inf.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
}

void print_minusgf(t_prntf *p, char *res, t_tuple info)
{
	const int len = info.pts + info.index;

	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
		buffer("1", 1, 0);
	buffer(res, len, 0);
	if (p->flags & HASH && p->flags & PRECIZ)
	{
		buffer(".", 1, 0);
		--p->width;
	}
	free(res);
	if (p->preciz > 0 && p->flags & HASH)
	{
		if (!info.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
	p->width -= len + ((p->preciz > 0) ? p->preciz + 1 : 0);
	p->width -= (p->preciz == -1);
	fill_space("          ", p->width);
}
