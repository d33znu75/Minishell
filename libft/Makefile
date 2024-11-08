# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 00:44:16 by rhmimchi          #+#    #+#              #
#    Updated: 2024/10/11 11:22:59 by abzaiz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_toupper.c ft_tolower.c ft_strlen.c ft_isprint.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putnbr_fd.c ft_putendl_fd.c ft_strjoin.c ft_substr.c ft_split.c ft_split_q.c\
	ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_free_list_chars.c \
	ft_isspace.c ft_skip_spaces.c ft_split2.c ft_multi_split.c ft_multi_split_utils.c ft_strndup.c ft_malloc.c

OBJS = $(SOURCES:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -rs $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
