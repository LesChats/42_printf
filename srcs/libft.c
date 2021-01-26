/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:54:20 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/26 21:09:28 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t					ft_strlen(const char *s)
{
	const char *const s_sav = s;

	while (*s)
		++s;
	return ((size_t)(s - s_sav));
}

static inline void		wordcopy(size_t dstp, size_t srcp, size_t len)
{
	register size_t a0;
	register size_t a1;

	if (len & 1)
	{
		((size_t *)dstp)[0] = ((size_t *)srcp)[0];
		if (len == 1)
			return ;
		srcp += 8;
		dstp += 8;
		len -= 1;
	}
	while (len)
	{
		a0 = ((size_t *)srcp)[0];
		a1 = ((size_t *)srcp)[1];
		((size_t *)dstp)[0] = a0;
		((size_t *)dstp)[1] = a1;
		srcp += 2 * 8;
		dstp += 2 * 8;
		len -= 2;
	}
}

void					*ft_memcpy(char *dest, const char *src, size_t n)
{
	size_t	dstp;
	size_t	srcp;

	if (dest == src)
		return (dest);
	dstp = (size_t)dest;
	srcp = (size_t)src;
	if (n >= 16)
	{
		wordcopy(dstp, srcp, n / 8);
		srcp += n & -8;
		dstp += n & -8;
		n %= 8;
	}
	while (n--)
		*(unsigned char *)dstp++ = *(unsigned char *)srcp++;
	return (dest);
}

int						ft_atoii(const char **str)
{
	unsigned char	c;
	long int		res;
	const char		*s;

	s = *str;
	res = 0;
	while (*s)
	{
		if ((c = *s++ - '0') > 9)
			return ((int)res);
		else
			res = (res << 1) + (res << 3) + c;
		(*str)++;
	}
	return ((int)res);
}

void					ft_bzero(void *s, size_t n)
{
	unsigned long	*dstp;
	unsigned char	*dstb;

	if (n >= 8)
	{
		dstp = (unsigned long*)s;
		while (n >= 8)
		{
			*dstp++ = Z;
			n -= 8;
		}
		dstb = (unsigned char*)dstp;
	}
	else
		dstb = (unsigned char*)s;
	while (n--)
		*dstb++ = 0;
}
