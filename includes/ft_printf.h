/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:03:19 by gcc               #+#    #+#             */
/*   Updated: 2021/01/27 01:15:39 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** includes
*/

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/*
** defines
*/

# define HIMAGIC	0x8080808080808080L
# define LOMAGIC	0x0101010101010101L
# define PC			0x2525252525252525L
# define Z 			0x0000000000000000L
# define BUFF_SZ	64
# define FLAGS_LST	"#-+ 0*"
# define HEX_U		"0123456789ABCDEF"
# define HEX_L		"0123456789abcdef"
# define HASH		0x1
# define MINUS		0x2
# define PLUS		0x4
# define SPACE		0x8
# define ZERO		0x10
# define WILLCARD	0x20
# define CHAR		0x40
# define LONG		0x80
# define LLONG		0x100
# define PRECIZ		0x200
# define UPPER		0x400
# define SHORT		0x800
# define ISNEG		0x1000
# define POINTER	0x2000

/*
** macros
*/

/*
** structures
*/

typedef struct	s_prntf
{
	size_t		flags;
	const char	*format;
	va_list		ap;
	int			width;
	int			preciz;
}				t_prntf;

typedef struct	s_bffr
{
	char	bff[BUFF_SZ];
	int		i;
	int		tlen;
}				t_bffr;

typedef	struct	s_string
{
	size_t	size;
	size_t	idx;
	char	*s;
	char	*save;
}				t_string;

/*
** 	Main functions
*/

int				ft_printf(const char *format, ...);
void			parse(t_prntf *p);

/*
** Convertions functions
*/

void			pf_putchar(t_prntf *p);
void			pf_putstr(t_prntf *p);
void			pf_putnbr(t_prntf *p);
void			pf_unsigned(t_prntf *p, const char c);
void			pf_adresse(t_prntf *p);
/*
** ------------- BONUS -----------------
*/
void			pf_floats(t_prntf *p);
void			pf_exponent(t_prntf *p);
void			pf_notfound(t_prntf *p);
void			pf_gishard(t_prntf *p);
void			pf_printlen(t_prntf *p);

/*
** Utils functions
*/

int				buffer(const char *str, size_t n, const char flush);
void			padding(int pad, const int zero);
int				get_len(long long x, int ans);
unsigned		wcharlen(unsigned c);
void			initializ_string(t_string *str);

/*
** libft functions
*/

size_t			ft_strlen(const char *s);
void			*ft_memcpy(char *dest, const char *src, size_t n);
int				ft_atoii(const char **str);
void			ft_bzero(void *s, size_t n);
#endif
