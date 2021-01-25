/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_gishard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:30:53 by gcc               #+#    #+#             */
/*   Updated: 2021/01/25 18:41:26 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

static int check_round(const char * s, int preciz)
{
	int tmp;

	tmp = -1;
	while (++tmp < preciz)
		if (!(*(s + tmp) == '9' || *(s + tmp) == '.'))
		   return (0);
	if (*(s + preciz) == '.')
		++preciz;
	if (*(s + preciz) > '4')
		return (1);	
	printf("because *s = %c\n", *(s+preciz));
	return (0);
}


static int16_t ex_count(const char *n, t_tuple n_info, const int preciz)
{
	int ans;

	ans = 0;
	if (n_info.pts == 0)
		ans = n_info.index - 1;
	else if (n_info.pts > 1)
		ans = n_info.pts - 1;
	else if (*n == '0')
	{
		--ans;
		while (*(n - ans + 1) == '0')
			--ans;
		n -= (ans - 1);
	}
	if (*n  == '9' && (ans || n_info.pts))
	{
		ans += check_round(n, preciz - 2);
	}
	return (ans);
}

static void	float_type(t_prntf *p, int preciz, char *res, t_tuple n_info)
{
	if (preciz != 0)
		p->flags &= ~PRECIZ; 
	if (n_info.pts)
		p->preciz = d_round(res, preciz, n_info.pts, &n_info.index);
	else 
		p->preciz = preciz;
	if (n_info.pts)
		if (!(p->flags & HASH))
		{
			while (*(res + n_info.pts + n_info.index - 1) == '0')
				--n_info.index;
			if (*(res + n_info.pts + n_info.index - 1) == '.')
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
	if (p->preciz != 0)
		p->flags &= ~PRECIZ; 
	pf_exponent_move_and_round(&p->preciz, &ex, &n_info, res);
	if (!(p->flags & HASH))
	{
			while (*(res + n_info.pts + n_info.index) == '0')
				--n_info.index;
			if (*(res + n_info.pts + n_info.index - 1) == '.')
				--n_info.index;
	}
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
	if (p->preciz == 0)
		++p->preciz;
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
	ex = ex_count(res, n_info, p->preciz + n_info.pts + 1);
	if ((p->preciz > ex && ex >= -4))
		return (float_type(p, p->preciz - (ex + 1), res, n_info));
	exponent_type(p, res, n_info, ex);
}
