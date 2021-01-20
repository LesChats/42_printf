/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:44:34 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/19 17:30:01 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DTOA_H
# define DTOA_H

# include "ft_printf.h"
# define EXPONENT_MAX   1023
# define MANTIS_SIZE    52
# define BIGINT_SIZE    300
# define DECIMAL_START  150

typedef struct  s_dbuff
{
    uint32_t        val[BIGINT_SIZE];
    uint16_t        start;
    uint16_t        end;
}               t_dbuff;

typedef struct  s_tuple
{
    int16_t     pts;
    int16_t    index;
}               t_tuple;

t_tuple     udtoa(double n, char **s);
t_dbuff     dbuff_init_zero();
t_dbuff     dbuff_init_unit(int16_t exponent);
void        dbuff_add_right_to_left(t_dbuff *left, const t_dbuff *const right);
void        dbuff_multiply_by_2_pow(t_dbuff *src, int16_t exponent);
void        dbuff_divided_by_2_pow(t_dbuff *src, int16_t exponent);
t_tuple     d_string(t_dbuff buff, char **res);
uint16_t    ft_itoa(uint32_t n, char *itoa_arr);
uint16_t    update_index(char *res, uint32_t n, uint16_t index);
uint16_t    get_len_int(uint32_t x);
char        *ft_strdup(char *src, int len);
#endif


