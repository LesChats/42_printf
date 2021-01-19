/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 06:25:29 by gcc               #+#    #+#             */
/*   Updated: 2020/12/28 18:53:32 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline size_t	byte_check(const char *cp, const char *s)
{
	if (!*cp)
		return (cp - s);
	if (!cp[1])
		return (cp - s + 1);
	if (!cp[2])
		return (cp - s + 2);
	if (!cp[3])
		return (cp - s + 3);
	if (!cp[4])
		return (cp - s + 4);
	if (!cp[5])
		return (cp - s + 5);
	if (!cp[6])
		return (cp - s + 6);
	if (!cp[7])
		return (cp - s + 7);
	return (0);
}

size_t					ft_strlen(const char *s)
{
	size_t		word;
	size_t		*s_ptr;
	size_t		ans;
	const char	*cpy;

	if (!*s)
		return (0);
	cpy = s;
	while ((size_t)cpy & 0b111)
		if (*cpy++ == 0)
			return (cpy - s - 1);
	s_ptr = (size_t *)cpy;
	while (1)
	{
		word = *s_ptr++;
		if (((word - LOMAGIC) & ~word & HIMAGIC))
			if ((ans = byte_check((const char *)(s_ptr - 1), s)))
				return (ans);
	}
}

static inline void	wordcopy(size_t dstp, size_t srcp, size_t len)
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

void				*ft_memcpy(char *dest, const char *src, size_t n)
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

//just for quick fix, will improv this later
int	ft_atoii(const char **str)
{
	unsigned char	c;
	long int	res;
	const char	*s; 
	
	s = *str;
	res = 0;
	if (!*s)
		(*str)++;
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
