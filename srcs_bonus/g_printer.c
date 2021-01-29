/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:07:14 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/29 04:03:15 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

void	printge(t_prntf *p, char *res, int16_t expon, t_tuple in)
{
	p->width -= (in.index + 5 + p->preciz) + (in.pts > 0);
	p->width -= (in.index || p->preciz > 0 || ((p->flags & HASH) & PRECIZ));
	if (p->preciz == -1)
		--p->width;
	else if (in.pts && in.index)
		++p->width;
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
	if (p->preciz == -1 && in.pts)
		buffer("1", 1, 0);
	buffer_exp(res, expon, in, p->preciz);
	free(res);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	if (p->preciz > 0 && p->flags & HASH)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
}

void	print_minusge(t_prntf *p, char *res, int16_t expon, t_tuple in)
{
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
	{
		if (in.pts)
			buffer("1", 1, 0);
		p->width -= 1 + (in.pts > 0);
	}
	else if (in.pts && in.index)
		++p->width;
	buffer_exp(res, expon, in, p->preciz);
	free(res);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	if (p->preciz > 0 && p->flags & HASH)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
	p->width -= in.index + 5 + p->preciz + (in.pts > 0);
	p->width -= (in.index || p->preciz > 0 || ((p->flags & HASH) & PRECIZ));
	fill_space("          ", p->width);
}

void	printgf(t_prntf *p, char *res, t_tuple inf)
{
	p->width -= inf.pts + inf.index + p->preciz + 1 + (inf.pts > 0);
	p->width -= ((p->preciz == -1) + (p->flags & HASH)) - (p->preciz == 0);
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
	buffer(res, inf.pts + inf.index + (inf.pts && inf.index), 0);
	free(res);
	if (p->flags & HASH && p->flags & PRECIZ)
		buffer(".", 1, 0);
	if (p->preciz > 0 && p->flags & HASH)
	{
		if (!inf.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
}

void	print_minusgf(t_prntf *p, char *res, t_tuple in)
{
	const int l = in.pts + in.index + (in.pts && in.index);

	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
		buffer("1", 1, 0);
	buffer(res, l, 0);
	free(res);
	if (p->flags & HASH && p->flags & PRECIZ)
	{
		buffer(".", 1, 0);
		--p->width;
	}
	if (p->preciz > 0 && p->flags & HASH)
	{
		if (!in.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
	p->width -= l + p->preciz + 1 + (p->preciz == -1) - (p->preciz == 0);
	fill_space("          ", p->width);
}
