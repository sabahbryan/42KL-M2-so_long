# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 17:04:56 by bryaloo           #+#    #+#              #
#    Updated: 2024/10/15 21:17:38 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME = so_long

# SOURCE FILES
SRCS 	=

# LIBFT
LIBFT_DIR = libft
LIBFT	= ${LIBFT_DIR}/libft.a

# OBJECTS
OBJS	=

# INCLUDES
INCLUDES	= -I ./ -I ${LIBFT_DIR}

# COMPILER & FLAGS
AR		= ar rcs
RM		= rm -f
GCC		= gcc
CFLAGS	= -Wall -Werror -Wextra

# MINILIBX
MLX_MACOS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
MLX_LINUX	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# MAKE & BUILD
all: 
bonus: 

${LIBFT}:
	make -C ${LIBFT_DIR}

$(NAME): $(OBJ)
	$(CC) $(OBJ) ${MLX_MACOS}
#	$(CC) $(OBJ) ${MLX_LINUX}

%.o: %.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ # MACOS
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# CLEANING
clean:
	${RM} 
	make -C ${LIBFT_DIR} ${LIBFT} clean

fclean:	clean
	${RM} 
	make -C ${LIBFT_DIR} ${LIBFT} clean

re:	fclean all

.PHONY:	all clean fclean re