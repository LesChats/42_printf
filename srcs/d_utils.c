/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:11:08 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/23 04:46:10 by gcc              ###   ########.fr       */
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

	*info -= pts;
	//printf("info = %d, pts = %d, preciz = %d\n", *info, pts, preciz);
	if (preciz >= *info)
	{
		//printf("ici ca lair ok\n");
		return (preciz - *info++);
	}
	preciz += pts + 1;
	//printf("preciz = %d\n", preciz);

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

int d_0round(char *s, int preciz, int16_t *info)
{
	const int p_save = preciz;
	char tmp;

	*info -= 1;
	//printf("info = %d, pts = 1, preciz = %d\n", *info, preciz);
	if (preciz > *info)
		return (preciz - *info);
	preciz += 1;
	//printf("preciz = %d\n", preciz);
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
	//printf(" 22 info = %d, pts = 1, preciz = %d\n", *info, preciz);
	//*info += (*info) ? 1 : 0;
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
