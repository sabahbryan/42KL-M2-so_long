# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 17:04:56 by bryaloo           #+#    #+#              #
#    Updated: 2024/10/11 22:20:58 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS 	=

LIBFT_DIR = libft

LIBFT	= ${LIBFT_DIR}/libft.a

OBJS	=

INCLUDES	= -I ./ -I ${LIBFT_DIR}

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: 
bonus: 

${LIBFT}:
	make -C ${LIBFT_DIR}

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) //MAC
#	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ //MAC
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	${RM} 
	make -C ${LIBFT_DIR} clean

fclean:	clean
	${RM} 
	make -C ${LIBFT_DIR} clean

re:	fclean all

.PHONY:	all clean fclean re