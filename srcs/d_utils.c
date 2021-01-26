/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:11:08 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/26 15:27:04 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

void	fill_space(char *filler, int size)
{
	while (size > 0)
	{
		buffer(filler, (size > 10) ? 10 : size, 0);
		size -= 10;
	}
}

void	buffer_exp(char *s, int ex, t_tuple info, int preciz)
{
	if (info.pts == 0)
	{
		buffer(s++, 1, 0);
		if (info.index || preciz > 0)
			buffer(".", 1, 0);
		buffer(s, info.index, 0);
	}
	else if (ex > 0)
		buffer(s, info.index + 1, 0);
	else
		buffer(s - ex, info.index + 1, 0);
}

void	nill_nan(char *ans, int len, size_t flags)
{
	len -= 3;
	if (flags & MINUS)
	{
		if (flags & ISNEG)
			buffer("-", 1, 0);
		buffer(ans, 3, 0);
		fill_space("          ", len);
	}
	else
	{
		fill_space("          ", len);
		if (flags & ISNEG)
			buffer("-", 1, 0);
		buffer(ans, 3, 0);
	}
	free(ans);
}
