/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:03:19 by gcc               #+#    #+#             */
/*   Updated: 2020/12/17 16:40:19 by gcc              ###   ########.fr       */
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
# include <stdio.h> //debug

/*
** defines
*/

# define HIMAGIC	0x8080808080808080L
# define LOMAGIC	0x0101010101010101L
# define PC		0x2525252525252525L
# define BUFF_SZ	64
# define FLAGS_LST	"#-+ 0*"
# define HEX_U		"0123456789ABCDEF"
# define HEX_L		"0123456789abcdef"
# define HASH		0b1
# define MINUS		0b10
# define PLUS		0b100
# define SPACE		0b1000
# define ZERO		0b10000
# define WILLCARD	0b100000
# define CHAR		0b1000000
# define LONG		0b10000000
# define LLONG		0b100000000
# define PRECIZ		0b1000000000
# define UPPER		0b10000000000
# define SHORT		0b100000000000
# define ISNEG		0b1000000000000
# define POINTER	0b10000000000000
/*
** macros
*/

# define ISNUM(x) (x > '0' && x < 58)

/*
** structures
*/

typedef struct		s_pflags
{
	size_t		flags;
	int		width;
	int		preciz;
}			t_pflags;
// metre a jour apres le premier debug
typedef struct		s_prntf
{
	size_t		flags;
	const char	*format;
	va_list		ap;
	int		width;
	int		preciz;
}			t_prntf;

typedef struct s_bffr
{
	char	bff[BUFF_SZ];
	int	i;
	int	tlen;
}		t_bffr;

typedef	struct s_string
{
	size_t size;
	size_t idx;
	char * s;
	char * save;
}		t_string;

/*
** Main function
*/

int	ft_printf(const char *format, ...);
void	parse(t_prntf *p);

/*
** Convertions functions
*/

void	pf_putchar(t_prntf *p);
void	pf_putstr(t_prntf *p);
void	pf_putnbr(t_prntf *p);
void	pf_unsigned(t_prntf *p, const char c);
void	pf_adresse(t_prntf *p);
/* comming soon 
void	pf_putpointet(t_prntf *p);
void	pf_putnbr_exp(t_prntf *p);
void	pf_putdouble(t_prntf *p);
*/

/*
** Utils functions
*/

int		buffer(const char *str, size_t n, const char flush);
void		padding_signed(const size_t flags, int pad);
void		padding(int pad, const int zero);
void		signes(const size_t flags);
int		get_len(long long x, int ans);
unsigned	wcharlen(unsigned c);
/*
** libft functions
*/

size_t	ft_strlen(const char *s);
void	*ft_memcpy(char *dest, const char *src, size_t n);
int	ft_atoii(const char **str);
#endif
