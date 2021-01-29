/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:59:04 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/28 20:03:41 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

static void	print(t_prntf *p, char *res, t_tuple inf)
{
	p->width -= inf.pts + inf.index + p->preciz + 1 + (inf.pts && inf.index);
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
	if (p->flags & HASH)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0)
	{
		if (!inf.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
}

static void	print_minus(t_prntf *p, char *res, t_tuple info)
{
	const int l = info.pts + info.index + (info.pts && info.index);

	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
		buffer("1", 1, 0);
	buffer(res, l, 0);
	if (p->flags & HASH)
	{
		buffer(".", 1, 0);
		--p->width;
	}
	free(res);
	if (p->preciz > 0)
	{
		if (!info.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
	p->width -= l + p->preciz + 1 + (p->preciz == -1) - (p->preciz == 0);
	fill_space("          ", p->width);
}

void		pf_floats(t_prntf *p)
{
	double	n;
	char	*res;
	t_tuple n_info;

	p->preciz = (p->flags & PRECIZ) ? p->preciz : 6;
	if (p->preciz != 0)
		p->flags &= ~HASH;
	n = va_arg(p->ap, double);
	if ((*(uint64_t *)&n >> 63))
	{
		p->flags |= ISNEG;
		n = -n;
		--p->width;
	}
	else if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	if ((n_info = udtoa(n, &res)).index == -1)
		return ;
	if (n_info.pts == -1)
		return (nill_nan(res, p->width, p->flags));
	if (n_info.pts)
		p->preciz = d_round(res, p->preciz, n_info.pts, &n_info.index);
	if (p->flags & MINUS)
		return (print_minus(p, res, n_info));
	print(p, res, n_info);
}
