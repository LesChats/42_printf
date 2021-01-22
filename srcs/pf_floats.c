/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pf_floats.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abaudot <abaudot@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/01/18 20:05:27 by abaudot		   #+#	#+#			 */
/*   Updated: 2021/01/21 16:42:15 by abaudot          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "dtoa.h"
#include <stdio.h>

//couper en 2 fonction 
//utiliser retour - 1

static void print(t_prntf *p, char *res, t_tuple info)
{
	const int len = info.pts + info.index;

	p->width -= len;
	fill_space("          ", p->width);
	if (p->flags & ISNEG)
		buffer("-", 1, 0);
	else if (p->flags & PLUS)
		buffer("+", 1, 0);
	else if (p->flags & SPACE)
		buffer(" ", 1, 0);
	if (p->preciz == -1)
		buffer("1", 1, 0);
	buffer(res, len, 0);
	free(res);
	if (p->preciz > 0)
	{
		if (!info.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
}

static void print_minus(t_prntf *p, char *res, t_tuple info)
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
	free(res);
	if (p->preciz > 0)
	{
		if (!info.pts)
			buffer(".", 1, 0);
		fill_space("0000000000", p->preciz);
	}
	p->width -= len;
	fill_space("          ", p->width);
}

void		pf_floats(t_prntf *p)
{
	double  n;
	char	*res;
	t_tuple n_info;

	if (!(p->flags & PRECIZ))
		p->preciz = 6;
	n = va_arg(p->ap, double);
	if ((*(uint64_t *)&n >> 63))
	{
		p->flags |= ISNEG;
		n = -n;
		--p->width;
	}
	else if (p->flags & PLUS || p->flags & SPACE)
		--p->width;
	n_info = udtoa(n, &res);
	if (n_info.index == -1)
		return;
//	n_info.index -= n_info.pts;
	if (n_info.pts > 0)
		p->preciz = d_round(res, p->preciz, n_info.pts + 1, &n_info.index);
//	else if (n_info.pts < 0)
//		n_info.pts = 0;
	if (p->flags & MINUS)
		return (print_minus(p, res, n_info));
	print(p, res, n_info);
}
