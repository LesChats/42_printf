# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 17:05:44 by abaudot           #+#    #+#              #
#    Updated: 2021/01/29 02:57:54 by abaudot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall -Wextra -Werror -O2 -fPIC

LIBFT = libft

NAME	=	libftprintf.a

DIR_S = srcs

BON_S = srcs_bonus

DIR_O = obj

HEADER = includes

SOURCES = ft_printf.c \
	  libft.c   \
	  pf_utils.c \
	  pf_parser.c \
	  pf_signed.c  \
	  pf_unsigned.c \
	  pf_string.c    \
	  pf_char.c       \
	  pf_notfound.c

BONUS_SRC = pf_floats.c	\
	  d_libft.c			 \
	  d_buff.c  		  \
	  d_utils.c  		   \
	  d_string.c		    \
	  pf_exponent.c			 \
	  pf_dtoa.c				  \
	  g_printer.c	    	   \
	  d_round.c       		    \
	  pf_gishard.c


SRCS 	= $(addprefix $(DIR_S)/,$(SOURCES))
BO_S 	= $(addprefix $(BON_S)/,$(BONUS_SRC))
OBJS 	= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))
B_OB 	= $(addprefix $(DIR_O)/,$(BONUS_SRC:.c=.o))

all: $(NAME)

bonus : all

$(NAME): $(OBJS) $(B_OB)
	ar rcs $(NAME) $(OBJS) $(B_OB)

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<
$(DIR_O)/%.o: $(BON_S)/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/
	@echo
	norminette ./$(BON_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean re norme all clean
