# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 17:04:56 by bryaloo           #+#    #+#              #
#    Updated: 2024/12/13 22:28:22 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME = so_long

# SOURCE FILES
SRCS	= main.c \
		  map_loader.c \
		  input_handler.c \
		  game_loop.c \
		  render.c \
		  validation.c

# LIBFT
LIBFT_DIR = libft
LIBFT	= ${LIBFT_DIR}/libft.a

# OBJECTS
OBJS	=  ${addprefix ./, ${SRCS:.c=.o}}

# INCLUDES
INCLUDES	= -I minilibx_linux -I ./ -I ${LIBFT_DIR}

# COMPILER & FLAGS
AR		= ar rcs
RM		= rm -f
GCC		= gcc
CFLAGS	= -Wall -Werror -Wextra

# MINILIBX
MLXFLAG		= -lmlx -lXext -lX11
#MLX_MACOS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
MLX_LINUX	= -Lminilibx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)

# MAKE & BUILD
all: ${LIBFT} ${NAME}

${LIBFT}:
	make -C ${LIBFT_DIR}

$(NAME): $(OBJS)
#	$(CC) $(OBJS) ${MLX_MACOS}
	$(GCC) $(OBJS) ${MLX_LINUX}

%.o: src/%.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@
#	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ # MACOS
	$(GCC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# CLEANING
clean:
	${RM} 
	make -C ${LIBFT_DIR} clean

fclean:	clean
	${RM} 
	make -C ${LIBFT_DIR} clean

re:	fclean all

.PHONY:	all clean fclean re