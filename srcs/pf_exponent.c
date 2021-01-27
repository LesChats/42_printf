/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_exponent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:50:27 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/27 03:57:20 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"
#include <stdio.h>

void		ft_atoiexpon(int16_t ex)
{
	char		ans_arr[4];
	uint16_t	size;

	if (ex >= 0)
	{
		if (ex < 10)
			buffer("e+0", 3, 0);
		else
			buffer("e+", 2, 0);
	}
	else if (ex < 0)
	{
		ex = -ex;
		if (ex > -10)
			buffer("e-0", 3, 0);
		else
			buffer("e-", 2, 0);
	}
	size = ft_itoa(ex, ans_arr);
	buffer(ans_arr, size, 0);
}

static void	print(t_prntf *p, char *res, int16_t expon, t_tuple info)
{
	p->width -= (info.index + 5 + p->preciz);
	p->width -= (p->flags & HASH || p->preciz > 0 || info.index);
	if (p->preciz == -1)
		p->width -= 1;
	else if (info.pts && info.index)
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
	if (p->preciz == -1 && info.pts)
		buffer("1", 1, 0);
	buffer_exp(res, expon, info, p->preciz);
	if (p->flags & HASH)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
}

static void	print_minus(t_prntf *p, char *res, int16_t expon, t_tuple info)
{
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
	{
		if (info.pts)
			buffer("1", 1, 0);
		p->width -= 1;
	}
	else if (info.pts && info.index)
		++p->width;
	buffer_exp(res, expon, info, p->preciz);
	if (p->flags & HASH)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
	p->width -= info.index + 5 + p->preciz;
	p->width -= (p->flags & HASH || p->preciz > 0 || info.index);// - (p->preciz > 0);
	fill_space("          ", p->width);
}

void		pf_exponent_move_and_round(int *preciz, int16_t *ex,
		t_tuple *info, char *res)
{
	if (info->pts == 0)
	{
		*ex = info->index - 1;
		*preciz = d_0round(res, *preciz, &info->index);
		if (*preciz == -1)
		{
			*res = '1';
			*ex += 1;
		}
	}
	else
	{
		*ex = mouv_pts(res, *preciz, info->pts, &info->index);
		*preciz = d_round(*ex < 0 ? res - *ex : res,
			*preciz, 1, &info->index);
		if (*preciz == -1)
		{
			*(res + 1) = '0';
			*res = '.';
			*ex += 1;
			info->index -= 1;
		}
	}
}

void		pf_exponent(t_prntf *p)
{
	double	n;
	char	*res;
	t_tuple	n_info;
	int16_t	ex;

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
	pf_exponent_move_and_round(&p->preciz, &ex, &n_info, res);
	if (p->flags & MINUS)
		return (print_minus(p, res, ex, n_info));
	print(p, res, ex, n_info);
}
