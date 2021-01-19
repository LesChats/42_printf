# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcc <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 13:11:20 by gcc               #+#    #+#              #
#    Updated: 2020/12/29 18:34:23 by gcc              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall -Wextra -Werror -O2 -fPIC

LIBFT = libft

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = ft_printf.c \
	  libft.c \
	  pf_utils.c \
	  pf_parser.c \
	  pf_signed.c \
	  pf_unsigned.c \
	  pf_string.c \
	  pf_char.c \
	  pf_decimal.c \
	  pf_floats.c \
	  pf_notfound.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

NAME=libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/ft_printf.h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

test:
	@make all misc/main.c

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean re norme all clean

