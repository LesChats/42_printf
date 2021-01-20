/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_string.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:40:29 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/19 22:26:49 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"
#include <stdio.h>

static uint16_t d_init(char *res, const uint16_t buff_start)
{
    uint16_t    i;
    uint16_t    index;

    index = 0;
    if (buff_start >= DECIMAL_START)
    {
        i = buff_start;
        *res = '0';
        ++index;
        if (buff_start > DECIMAL_START)
            *(res + index++) = '.';
        while (i-- > DECIMAL_START)
        {
            ft_memcpy(res + index, "000000000", 9);
            index += 9;
        }
    }
    return (index);
}

static uint16_t d_load_number(char *res, t_dbuff *buff,
        uint16_t i, uint16_t id)
{
    char        itoa_arr[10];
    uint16_t    k;
    uint16_t    j;

    if (i == buff->start && i < DECIMAL_START)
        id += update_index(res, buff->val[i], id);
    else if (i == buff->end && i >= DECIMAL_START)
    {
        k = 9 - get_len_int(buff->val[i]);
        while (k--)
            res[id++] = '0';
        while ((buff->val[i] % 10) == 0 && buff->val[i])
            buff->val[i] /= 10;
        id += update_index(res, buff->val[i], id);
    }
    else
    {
        k = ft_itoa(buff->val[i], itoa_arr);
        j = k;
        while (j++ < 9)
            res[id++] = '0';
        ft_memcpy(res + id, itoa_arr, k);
        id += k;
    }
    return (id);
}

t_tuple    d_string(t_dbuff buff, char **res)
{
    uint16_t    i;
    t_tuple     ans;

    ans.index = -1;
    ans.pts = 0;
    if (!(*res = (char *)malloc((buff.end - buff.start + 1) * 9 + 1)))
        return (ans);
    if ((ans.index = d_init(*res, buff.start)))
        ans.pts = 1;
    i = buff.start - 1;
    while (++i <= buff.end)
    {
        if (i == DECIMAL_START)
            if (ans.index > buff.start || (buff.start != buff.end) || ans.pts)
            {
                ans.pts = ans.index;
                *(*res + ans.index++) = '.';
            }
        ans.index = d_load_number(*res, &buff, i, ans.index);
    }
        *(*res + ans.index) = 0;
    return (ans);
}
