/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_buff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:02 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/26 13:45:04 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

t_dbuff		dbuff_init_zero(void)
{
	t_dbuff res;

	ft_bzero(&res, sizeof(res));
	res.start = BIGINT_SIZE - 1;
	res.end = 0;
	return (res);
}

t_dbuff		dbuff_init_unit(int16_t exponent)
{
	t_dbuff res;

	ft_bzero(&res, sizeof(res));
	res.val[DECIMAL_START - 1] = 1;
	res.start = DECIMAL_START - 1;
	res.end = res.start;
	if (exponent < 0)
		dbuff_divided_by_2_pow(&res, exponent);
	else if (exponent > 0)
		dbuff_multiply_by_2_pow(&res, exponent);
	return (res);
}

void		dbuff_add_right_to_left(t_dbuff *left, const t_dbuff *const right)
{
	uint16_t	start;
	uint16_t	end;
	uint16_t	i;

	start = left->start < right->start ? left->start : right->start;
	end = left->end > right->end ? left->end : right->end;
	i = end;
	while (i >= start)
	{
		(left->val)[i] += (right->val)[i];
		if ((left->val)[i] >= 1000000000)
		{
			(left->val)[i] -= 1000000000;
			(left->val)[i - 1] += 1;
		}
		--i;
		if (i < start && (left->val)[i] != 0)
			--start;
	}
	left->end = end;
	left->start = start;
}

void		dbuff_multiply_by_2_pow(t_dbuff *src, int16_t exponent)
{
	uint16_t	i;

	while (exponent--)
	{
		i = src->start;
		while (i <= src->end)
		{
			(src->val)[i] <<= 1;
			if ((src->val)[i] >= 1000000000)
			{
				(src->val)[i] -= 1000000000;
				(src->val)[i - 1] += 1;
				if (i == src->start)
					--(src->start);
			}
			if (i == src->end && (src->val)[i] == 0)
				--(src->end);
			++i;
		}
	}
}

void		dbuff_divided_by_2_pow(t_dbuff *src, int16_t exponent)
{
	uint16_t	i;

	while (exponent++)
	{
		i = src->end;
		while (i >= src->start)
		{
			if ((src->val)[i] & 1)
			{
				(src->val)[i + 1] += 500000000;
				if (i == src->end)
					++(src->end);
			}
			(src->val)[i] >>= 1;
			if (i == src->start && (src->val)[i] == 0)
				++(src->start);
			--i;
		}
	}
}
