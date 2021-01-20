/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:05:27 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/20 01:05:00 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtoa.h"
#include <stdio.h>

static int d_round(char *s, int preciz, int16_t *info)
{
    const int p_save = preciz;

    if (preciz >= *info)
        return (preciz - *info + 1);
    if (*(s + preciz) > '4')
    {
        while (++preciz < *info)
            if (*(s + preciz) > '0')
            {
                s += p_save;
                while (*--s == '9')
                    *s = '0';
                if (*s == '.')
                    while (*--s == '9')
                        *s = '0';
                *s += 1;
                break ;
            }
    }
    *info = p_save;
    if (p_save)
        ++*info;
    return (0);
}

static void print(t_prntf *p, char *res, t_tuple info)
{
    const int len = info.pts + info.index;

    p->width -= len;
    while (p->width > 0)
    {
        buffer("          ", (p->width > 10) ? 10 : p->width, 0);
        p->width -= 10;
    }
    if (p->flags & ISNEG)
        buffer("-", 1, 0);
    else if (p->flags & PLUS)
        buffer("+", 1, 0);
    else if (p->flags & SPACE)
        buffer(" ", 1, 0);
    buffer(res, len, 0);
    if (p->preciz > 0)
    {
        if (!info.pts)
            buffer(".", 1, 0);
        while (p->preciz > 0)
        {
            buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
            p->preciz -= 10;
        }
    }
}

static void print_minus(t_prntf *p, char *res, t_tuple info)
{
    const int len = (info.pts > 0) ? info.pts + p->preciz + 1 : info.index;

    if (p->flags & ISNEG)
        buffer("-", 1, 0);
    else if (p->flags & PLUS)
        buffer("+", 1, 0);
    else if (p->flags & SPACE)
        buffer(" ", 1, 0);
    buffer(res, len, 0);
    if (p->preciz > 0)
    {
        if (!info.pts)
            buffer(".", 1, 0);
        while (p->preciz > 0)
        {
            buffer("0000000000", (p->preciz > 10) ? 10 : p->preciz, 0);
            p->width -= 10;
        }
    }
    p->width -= len;
    while (p->width > 0)
    {
        buffer("          ", (p->width > 10) ? 10 : p->width, 0);
        p->preciz -= 10;
    }
}

void        pf_floats(t_prntf *p)
{
    double  n;
    char    *res;
    t_tuple n_info;

    if (!(p->flags & PRECIZ))
        p->preciz = 6;
    n = va_arg(p->ap, double);
    if ((*(uint64_t *)&n >> 63))
    {
        p->flags |= ISNEG;
        n = -n;
        --p->width;
    }
    else if (p->flags & PLUS || p->flags & SPACE)
        --p->width;
    n_info = udtoa(n, &res);
    if (n_info.index == -1)
        return;
    n_info.index -= n_info.pts;
    if (n_info.pts > 0)
        p->preciz = d_round(res + n_info.pts + 1, p->preciz,
                &n_info.index);
    if (p->flags & MINUS)
        return (print_minus(p, res, n_info));
    print(p, res, n_info);
}
