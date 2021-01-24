/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_gishard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:30:53 by gcc               #+#    #+#             */
/*   Updated: 2021/01/24 23:10:16 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

static int16_t ex_count(t_tuple n_info)
{
	if (n_info.pts == 0)
		return (n_info.index - 1);
	if (n_info.pts == 1)
		return (0);
	return (n_info.pts - 1);
}

static void	float_type(t_prntf *p, int preciz, char *res, t_tuple n_info)
{
	if (n_info.pts)
		p->preciz = d_round(res, preciz, n_info.pts, &n_info.index);
	if (!(p->flags & HASH))
	{
		while (*(res + n_info.pts + n_info.index - 1) == '0')
			--n_info.index;
	}
	 if (p->flags & MINUS)
		return (print_minusgf(p, res, n_info));
	printgf(p, res, n_info);
}

static void	exponent_type(t_prntf *p, char *res, t_tuple n_info, int16_t ex)
{
	if (p->preciz)
		p->preciz -= 1;
	pf_exponent_move_and_round(&p->preciz, &ex, &n_info, res);
	//if (!(p->flags & HASH))
	 if (p->flags & MINUS)
		return (print_minusge(p, res, ex, n_info));
	printge(p, res, ex, n_info);
}

void	pf_gishard(t_prntf *p)
{
	double	n;
	char	*res;
	t_tuple n_info;
	int16_t	ex;

	if (!(p->flags & PRECIZ))
		p->preciz = 6;
	if (p->preciz != 0)
		p->flags &= ~PRECIZ; 
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
	ex = ex_count(n_info);
	if (p->preciz > ex && ex >= -4)
		return (float_type(p, p->preciz - (ex + 1), res, n_info));
	exponent_type(p, res, n_info, ex);
}
