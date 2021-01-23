/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_exponent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:50:27 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/23 04:35:20 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"
#include <stdio.h>

static	void ft_atoiexpon(int16_t ex)
{
	char ans_arr[4];
	uint16_t size;

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

static void print(t_prntf *p, char *res, int16_t expon, t_tuple info)
{
//	printf("wi = %d, pre = %d, ind = %d pts = %d\n", p->width, p->preciz, info.index, info.pts); 
	p->width -= /*(expon > 99) ?*/ (info.index + 5 + p->preciz) ;//: (info.index + 6 + p->preciz);
//	printf("wi = %d, pre = %d, ind = %d\n", p->width, p->preciz, info.index); 
	if (info.index || p->preciz > 0 || p->flags & HASH)
	 	p->width--;
	//if (p->flags & HASH)
	//	p->width--;
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
	if (p->flags & HASH)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
}

static void print_minus(t_prntf *p, char *res, int16_t expon, t_tuple info)
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
	if (p->flags & HASH)
		buffer(".", 1, 0);
	free(res);
	if (p->preciz > 0)
		fill_space("0000000000", p->preciz);
	ft_atoiexpon(expon);
	p->width -= info.index + 5 + p->preciz;
	if (info.index || p->preciz > 0 || p->flags & HASH)
	 	p->width--;	
	//padding(p->width, p->flags & ZERO);
	fill_space("          ", p->width);
}

static void	pf_exponent_move_and_round(int *preciz, int16_t *ex,
		t_tuple *info, char *res)
{
	if (info->pts == 0)
	{
		*ex = info->index - 1;
		*preciz = d_0round(res, *preciz, &info->index);
		if (*preciz == -1)
		{
		//	*(res - *ex + 2) = '0';
			*res = '1';
			*ex += 1;
		//	printf("icicici %d \n",info->index);
		}
		return ;
	}
	else 
	{
		*ex = mouv_pts(res, info->pts, &info->index);
		*preciz = d_round(*ex < 0 ? res - *ex : res,
			*preciz, 1, &info->index);
	}
	//printf("la p = %d index = %d\n", *preciz, info->index);
	if (*preciz == -1)
	{
		*(res + 1) = '0';
		*res = '.';
		*ex += 1;
		info->index -= 1;

	}
	//else if (info->pts == 0 && *preciz >= info->index)
	//*preciz -= 1;
	//printf("ici p = %d\n", *preciz);
	//else if (*preciz)
	//	++*preciz;
}

void	pf_exponent(t_prntf *p)
{
	double	n;
	char	*res;
	t_tuple	n_info;
	int16_t	ex;

	if (!(p->flags & PRECIZ))
		p->preciz = 6;
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
	n_info = udtoa(n, &res);
	if (n_info.index == -1)
		return ;
	if (n_info.pts == -1)
		return (nill_nan(res, p->width, p->flags));
	pf_exponent_move_and_round(&p->preciz, &ex, &n_info, res);
	if (p->flags & MINUS)
		return (print_minus(p, res, ex, n_info));
	print(p, res, ex, n_info);
}
