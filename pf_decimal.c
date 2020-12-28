/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 02:30:30 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 11:00:40 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int last_decimal(char *str, double decimal, int idx)
{
	double	tmp;
	int	unity;

	decimal *= 10.0;
	tmp = decimal - (double)((int)decimal);
	printf("f = %f\n", tmp);
	if (tmp >= 0.5)
		++decimal;
	unity = (int)decimal;
	if (unity == 10)
	{
		if (!idx)
			return (1);
		str[idx] = '0';
		while (idx && str[idx - 1] == '9')
			str[--idx] = '0';
		if (!idx)
			return (1);
		++str[idx - 1];
	}
	else
		str[idx] = '0' + unity;
	return (0);
}

int      fill_decimals(char *str, double decimal, int size)
{
	double	tmp;
	int	unity;
	int	idx;
	
	idx = 0;
	while (--size)
	{
		decimal *= 10.0;
		unity = (int)decimal;
		str[idx++] = '0' + unity;
		decimal -= (double)unity;
	}
	return (last_decimal(str, decimal, idx));
}
