/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_round.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:49:02 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/28 20:04:03 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"

static int	check_round(char *s, int prez)
{
	char *const s_sav = s - 1;

	s += prez - 1;
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

static int	special_round(char *res, int prez)
{
	int tmp;

	tmp = -1;
	res += 2;
	while (++tmp < prez)
		if (*(res + tmp) != '9')
			return (0);
	if (*(res + prez) > '4')
	{
		*(res - 2) = '.';
		*(res - 3) = '1';
		while (prez > -2)
			*(res + prez--) = '0';
		return (1);
	}
	return (0);
}

int			d_0round(char *s, int prez, int16_t *info)
{
	const int	p_sv = prez;
	char		tmp;

	if (prez >= *info)
		return (prez - --*info);
	prez += 1;
	tmp = *(s + prez);
	if (tmp > '4')
	{
		if (tmp > '5')
			prez = check_round(s, prez);
		else
		{
			if (*info > prez + 1)
				prez = check_round(s, p_sv + 1);
			else
			{
				prez -= 1;
				prez = (*(s + prez) % 2) ? check_round(s, p_sv + 1) : 0;
			}
		}
	}
	prez = (prez != -1) ? 0 : -1;
	*info = p_sv;
	return (prez);
}

int			d_round(char *s, int prez, int16_t pts, int16_t *info)
{
	const int	p_sv = prez;
	const char	tmp = *(s + prez + pts + 1);

	*info -= pts;
	if (prez >= *info)
		return (prez - *info);
	prez += pts + 1;
	if (tmp > '4')
	{
		if (tmp > '5')
			prez = check_round(s, prez);
		else
		{
			if (*info > prez)
				prez = check_round(s, p_sv + pts + 1);
			else
			{
				prez -= *(s + prez - 1) == '.' ? 2 : 1;
				prez = (*(s + prez) % 2) ? check_round(s, p_sv + pts + 1) : 0;
			}
		}
	}
	prez = (prez != -1) ? 0 : -1;
	*info = p_sv;
	return (prez);
}

int16_t		mouv_pts(char *res, int prez, int16_t pts, int16_t *info)
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
			ans += special_round(res, prez);
		*info += ans;
	}
	return (ans);
}
