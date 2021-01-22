/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:11:08 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/22 04:29:10 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

//objectif metre a jour le nombre de decimal
//retourner la presizion
//prevoir le cas ou je depasse la len
static int	check_round(char *s, int preciz)
{
	char * const s_sav = s - 1;

	s += preciz - 1;
	while (*s == '9' && s > s_sav)
		*s-- = '0';
	if (*s == '.')
	{
		--s;
		while (*s == '9' && s > s_sav)
			*s-- = '0';
	}
	if (s == s_sav)
		return (-1);
	else
		*s += 1;
	return (0);
}


int d_round(char *s, int preciz, int16_t pts, int16_t *info)
{
	const int p_save = preciz;
	char tmp;

	*info -= (pts - 1);
	if (preciz >= *info)
		return (preciz - *info + 1);
	preciz += pts;
	tmp = *(s + preciz);
	if (tmp > '4')
	{
		if (tmp > '5')
			preciz = check_round(s, preciz);
		else
			while (++preciz < *info)
			{
				if (*(s + preciz) > '0')
				{
					preciz = check_round(s, p_save + pts);
					break ;
				}
			}
	}
	else
		preciz = 0;
	*info = p_save + 1;
	return (preciz);
}

void	fill_space(char *filler, int size)
{
	while (size > 0)
	{
		buffer(filler, (size > 10) ? 10 : size, 0);
		size -= 10;
	}
}

int16_t	mouv_pts(char *res, int16_t pts, int16_t *info)
{
	uint16_t ans;

	ans = 0;
	if (pts > 1)
	{
		ans = pts - 1;
		while (pts > 1)
		{
			ft_sswap(res + pts, res + pts - 1);
			--pts;
		}
	}
	else if (*res++ == '0')
	{
		ans -= 1;
		while (*(res + 1) == '0')
		{
			res += 1;
			--ans;
		}
		*res = *(res + 1);
		*(res + 1) = '.';
		*info += ans;
	}
	return (ans);
}

void	buffer_exp(char *s, int ex, t_tuple info)
{
	if (info.pts < 0)
	{
		buffer(s, info.index, 0);
		return ;
	}
	if (info.pts == 0)
	{
		buffer(s++, 1, 0);
		buffer(".", 1, 0);
		buffer(s, info.index, 0);
	}
	else if (ex > 0)
		buffer(s, info.index + 1 , 0);
	else
		buffer(s - ex, info.index + 1, 0);
}
