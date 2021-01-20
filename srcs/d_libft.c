/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_libft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 01:03:28 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/19 17:26:33 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "dtoa.h"

uint16_t    get_len_int(uint32_t x)
{
    if (x >= 1000000000)
        return (10);
    if (x >= 100000000)
        return (9);
    if (x >= 10000000)
        return (8);
    if (x >= 1000000)
        return (7);
    if (x >= 100000)
        return (6);
    if (x >= 10000)
        return (5);
    if (x >= 1000)
        return (4);
    if (x >= 100)
        return (3);
    if (x >= 10)
        return (2);
    return (1);
}

uint16_t    ft_itoa(uint32_t n, char *itoa_arr)
{
    const uint16_t  len = get_len_int(n);

    itoa_arr += len;
    if (!n)
        *--itoa_arr = '0';
    while (n)
    {
        *--itoa_arr = '0' + (n % 10);
        n /= 10;
    }
    return (len);
}

uint16_t    update_index(char *res, uint32_t n, uint16_t index)
{
    char            itoa_arr[11];
    const uint16_t  itoa_len = ft_itoa(n, itoa_arr);
    ft_memcpy(res + index, itoa_arr, itoa_len);
    return (itoa_len);
}
/******************************************/

char *  ft_strdup(char *src, int len)
{
    char *ans;

    if (!(ans = (char *)malloc(len + 1)))
        return (0);
    ft_memcpy(ans, src, len);
    *(ans + len) = 0;
    return (ans);
}
