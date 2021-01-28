/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:04:10 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/28 16:21:02 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DTOA_H
# define DTOA_H

# include "ft_printf.h"
# define EXPONENT_MAX   1023
# define MANTIS_SIZE	52
# define BIGINT_SIZE	300
# define DECIMAL_START  150

typedef struct	s_dbuff
{
	uint32_t	val[BIGINT_SIZE];
	uint16_t	start;
	uint16_t	end;
}				t_dbuff;

typedef struct	s_tuple
{
	int16_t	pts;
	int16_t	index;
}				t_tuple;

/*
**			DTOA_PART
*/

t_tuple			udtoa(double n, char **s);
t_dbuff			dbuff_init_zero();
t_dbuff			dbuff_init_unit(int16_t exponent);
void			dbuff_add_right_to_left(t_dbuff *left,
		const t_dbuff *const right);
void			dbuff_multiply_by_2_pow(t_dbuff *src, int16_t exponent);
void			dbuff_divided_by_2_pow(t_dbuff *src, int16_t exponent);
t_tuple			d_string(t_dbuff buff, char **res);
uint16_t		update_index(char *res, uint32_t n, uint16_t index);
uint16_t		get_len_int(uint32_t x);
char			*ft_strdup(char *src, int len);

/*
**		handel rounding on string
*/

int				d_round(char *s, size_t *flags, int preciz, t_tuple *t);
int				d_0round(char *s, int preciz, int16_t *info);
void			fill_space(char *filler, int size);
/*
**			for %e
*/
int16_t			mouv_pts(char *res, int preciz, int16_t pts, int16_t *info);
void			pf_exponent_move_and_round(t_prntf *p, int16_t *ex,
		t_tuple *info, char *res);
void			buffer_exp(char *s, int ex, t_tuple info, int preciz);
void			ft_sswap(char *a, char *b);
void			ft_atoiexpon(int16_t ex);

/*
**			utils
*/

void			nill_nan(char *ans, int len, size_t flags);
uint16_t		ft_itoa(uint32_t n, char *itoa_arr);

/*
**		g_printer.c for %g
*/

void			printge(t_prntf *p, char *res, int16_t expon, t_tuple info);
void			print_minusge(t_prntf *p, char *res,
		int16_t expon, t_tuple info);
void			printgf(t_prntf *p, char *res, t_tuple inf);
void			print_minusgf(t_prntf *p, char *res, t_tuple info);
#endif
