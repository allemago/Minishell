# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:33:32 by magrabko          #+#    #+#              #
#    Updated: 2025/03/04 10:30:46 by magrabko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= 		libft.a 

CCFLAGS= 	-Wall -Werror -Wextra -g3

SRC=		ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c			\
			ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c		\
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putnbr_fd.c				\
			ft_putstr_fd.c ft_strchr.c ft_strndup.c	ft_strdup.c ft_strlcat.c	\
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c		\
			ft_substr.c ft_strjoin.c ft_tolower.c ft_toupper.c ft_split.c 		\
			ft_calloc.c ft_strtrim.c ft_striteri.c ft_strmapi.c ft_itoa.c		\
			ft_putendl_fd.c ft_printf_fd.c ft_putptr_fd.c ft_putnbr_base_fd.c	\

OBJ = $(SRC:.c=.o)

%.o: %.c
	@cc $(CCFLAGS) -c $< -o $@


$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

all: $(NAME)
	
clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f libft.a

re: fclean all
