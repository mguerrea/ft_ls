# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/14 14:59:46 by mguerrea          #+#    #+#              #
#    Updated: 2018/12/21 13:36:40 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE	:= make
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

SRCDIR	:=	./
INCLDIR	:=	-I libft/includes
LIBDIR 	:=	libft/

CFLAGS	:=	-Wall -Wextra -Werror $(INCLDIR)
LDFLAGS	:=	-L$(LIBDIR) -lft

SRCS    :=	main.c			\
			max.c			\
			count.c		\
			files.c			\
			flags.c			\
			base_functions.c	\
			format_functions.c			\
			free.c \
			rights.c \
			sort_functions.c \
			print.c \
			ft_ls.c \
			errors.c \
			sort_functions_bonus.c \
			print_items.c \
			print_bonus.c 
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(patsubst %.c,%.o,$(SRCS))
DEPS	:=	Makefile ft_ls.h
LIB		:=	$(LIBDIR)/libft.a
NAME	:=	ft_ls

# Colors
GREEN			=	\033[32m
RESET			=	\033[0m

all: $(NAME)

$(LIB):
	@$(MAKE) -C libft/

$(NAME): $(LIB) $(OBJS)
	@echo "\033[32m  Creating: \033[0m$(NAME)"
	@$(LD) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(DEPS)
	@printf "\033[32m Compiling: \033[0m$< -> $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

libft-clean:
	make -C $(LIBDIR) clean

libft-fclean:
	make -C $(LIBDIR) fclean

clean: libft-clean
	rm -rf $(OBJS)

fclean: clean libft-fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all libft libft-clean libft-fclean clean fclean re