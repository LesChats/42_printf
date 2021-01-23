/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:13:31 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/22 12:24:42 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"
#include <string.h>
#include <stdio.h>

static t_tuple d_nan(uint64_t mantissa, char **s)
{
    t_tuple ans;

    ans.pts = -1;
    ans.index = 3;
    if (mantissa == 0 ||mantissa >> 63 != 0)
    {
        if (!(*s = ft_strdup("inf", 3)))
            ans.index = -1;
    }
    else
    {
        if (!(*s = ft_strdup("nan", 3)))
            ans.index = -1;
    }
    return (ans);
}

static t_tuple d_zero(char **s)
{
    t_tuple ans;

    ans.pts = 0;
    ans.index = 1;
    if (!(*s = ft_strdup("0", 1)))
        ans.index = -1;
    return (ans);
}


t_tuple udtoa(double n, char **s)
{
    uint64_t    mantissa;
    int16_t     exponent;
    t_dbuff     unit;
    t_dbuff     result;
    int16_t     i;

    mantissa = (*(uint64_t*)&n << 12) >> 12;
    exponent = ((*(uint64_t*)&n << 1) >> 53) - EXPONENT_MAX;
    if (n == 0)
        return d_zero(s);
    if (exponent >= EXPONENT_MAX + 1)
        return d_nan(mantissa, s);
    unit = dbuff_init_unit(exponent - MANTIS_SIZE);
    result = dbuff_init_zero();
    i = -1;
    while (++i < MANTIS_SIZE)
    {
        if ((mantissa >> i) & 1)
            dbuff_add_right_to_left(&result, &unit);
        dbuff_multiply_by_2_pow(&unit, 1);
    }
    dbuff_add_right_to_left(&result, &unit);
    return (d_string(result, s));
}

/*
 * ** Provided for testing
 * 
 

int     main(int ac, char **av)
{
    double  x;
    char    *s;

    if (ac < 2)
        return (-1);
    x = atof(av[1]);
    printf("Printf conversion: %.100f\n", x);
    t_tuple i = udtoa(x, &s);
    printf("Dtoa conversion:   %s\n", s);
    printf("virgule = %d  ->%c<-\n", i.pts, s[i.pts]);
    free(s);
    return (0);
}
*/
