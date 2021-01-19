/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 02:30:30 by gcc               #+#    #+#             */
/*   Updated: 2020/12/29 16:55:03 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int last_decimal(char *str, double decimal, int idx, int size)
{
	double	tmp;
	int	unity;

	decimal *= 10.0;
	if (size < 0 && decimal >= 5)
		return (1);
	tmp = decimal - (double)((int)decimal);
	//printf("\n tmp = %.20f dec = %f\n", tmp, decimal);
	if (tmp >= 0.5)
		++decimal;
	//else if (((int)decimal % 2) && tmp >= 0.5)
	//	++decimal;
	unity = (int)decimal;
	if (unity == 10)
	{
		str[idx] = '0';
		if (!idx)
			return (1);
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

static int last_zdecimal(char *str, double decimal, int idx, int size)
{
	double	tmp;
	int	unity;
	
	decimal *= 10.0;
	if (size < 0 && decimal > 5)
		return (1);
	tmp = decimal - (double)((int)decimal);
	if (tmp > 0.5)
		++decimal;
	//else if (!((int)decimal % 2) && tmp >= 0.5)
	//	++decimal;
	unity = (int)decimal;
	if (unity == 10)
	{
		str[idx] = '0';
		if (!idx)
			return (1);
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

int      fill_decimals(char *str, double decimal, int size, char zero)
{
	int	unity;
	int	idx;
	
	idx = 0;
	while (--size > 0)
	{
		decimal *= 10.0;
		unity = (int)decimal;
		str[idx++] = '0' + unity;
		decimal -= (double)unity;
	}
	if (zero)
		return (last_decimal(str, decimal, idx, size));
	else
		return (last_zdecimal(str, decimal, idx, size));
}
