# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 20:21:41 by bryaloo           #+#    #+#              #
#    Updated: 2024/10/11 22:01:16 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	=	ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_atoi.c \
			ft_itoa.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_split.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstmap.c \
			ft_printf.c \
			ft_printf_utils_1.c \
			ft_printf_utils_2.c \
			ft_printf_utils_3.c \
			get_next_line.c \

OBJS	= ${addprefix objs/, ${SRCS:.c=.o}}

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

objs/%.o: %.c
	mkdir -p objs
	${GCC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${AR} $@ ${OBJS}

clean:
	${RM} ${OBJS} ${NAME}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re