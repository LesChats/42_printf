/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_round.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:49:02 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/25 16:20:36 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

static  int check_round(char *s, int preciz)
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
	*s += 1;
	return (0);
}

static int special_round(char *res, int preciz)
{
	int tmp;

	tmp = -1;
	res += 2;
	while (++tmp < preciz)
		if (*(res + tmp) != '9')
			return (0);
	if (*(res + preciz) > '4')
	{
		*(res - 2) = '.';
		*(res - 3) = '1';
		while (preciz > -2)
			*(res + preciz--) = '0';
		return (1);
	}
	return (0);
}

int d_0round(char *s, int preciz, int16_t *info)
{
	const int p_save = preciz;
	char tmp;

	*info -= 1;
	if (preciz > *info)
		return (preciz - *info);
	preciz += 1;
	tmp = *(s + preciz);
	if (tmp > '4')
	{
		if (tmp > '5')
			preciz = check_round(s, preciz);
		else
			if (*info > preciz)
				preciz = check_round(s, p_save + 1);
			else
			{
				preciz -= *(s + preciz - 1) == '.' ? 2 : 1;

				if (*(s + preciz) % 2)
					preciz = check_round(s, p_save + 1);
			}
	}
	preciz = (preciz != -1) ? 0 : -1;
	*info = p_save;
	return (preciz);
}

int d_round(char *s, int preciz, int16_t pts, int16_t *info)
{
	const int p_save = preciz;
	char tmp;

	*info -= pts;
	if (preciz >= *info)
		return (preciz - *info++);
	preciz += pts + 1;
	tmp = *(s + preciz);
	if (tmp > '4')
	{
		if (tmp > '5')
			preciz = check_round(s, preciz);
		else
			if (*info > preciz)
				preciz = check_round(s, p_save + pts + 1);
			else
			{
				preciz -= *(s + preciz - 1) == '.' ? 2 : 1;
				if (*(s + preciz) % 2)
					preciz = check_round(s, p_save + pts + 1);
			}
	}
	preciz = (preciz != -1) ? 0 : -1;
	*info = p_save;
	*info += (*info) ? 1 : 0;
	return (preciz);
}

int16_t mouv_pts(char *res, int preciz, int16_t pts, int16_t *info)
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
	else if (*res == '0')
	{
		ans -= 1;
		while (*(++res + 1) == '0')
			--ans;
		*res = *(res + 1);
		*(res + 1) = '.';
		if (*res == '9')
			ans += special_round(res, preciz);
		*info += ans;
	}
	return (ans);
}
