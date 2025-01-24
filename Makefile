# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 17:04:56 by bryaloo           #+#    #+#              #
#    Updated: 2025/01/24 16:51:54 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Detect the operating system
UNAME_S := $(shell uname -s)

NAME = so_long
SRCS = $(wildcard src/*.c)
HEADER = -Iincludes
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
CC = cc
CFLAGS =  -g -Wall -Wextra -Werror

# OS settings
ifeq ($(UNAME_S), Linux)
	# Linux flags
	MLX_DIR = minilibx_linux/
	MLX = $(MLX_DIR)libmlx.a
	MLX_FLAGS = -lmlx -L/usr/lib -lXext -lX11 -lm #-lmlx -lX11 -lXext -lm
else ifeq ($(UNAME_S), Darwin)
	# macOS flags
	MLX_DIR = minilibx_linux/
	MLX = $(MLX_DIR)libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error Unsupported OS: $(UNAME_S))
endif

# Terminal Colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
AQUA = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(SRCS) Makefile so_long.h
	@echo "\n$(YELLOW)Setting DISPLAY ENV...$(RESET)"
	@echo "export DISPLAY=:0" >> ~/.bashrc
	@echo "$(GREEN)DISPLAY ENV set to :0$(RESET)"
	@echo "$(YELLOW)\nCompiling so_long executable...$(RESET)"
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)
	@echo "$(AQUA)so_long executable compiled$(RESET)"

$(LIBFT): FORCE
	@echo "\n$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) -s

$(MLX): FORCE
	@echo "\n$(YELLOW)Compiling minilibx...$(RESET)"
	@chmod 777 $(MLX_DIR)/configure
	@make -C $(MLX_DIR) -s > /dev/null 2>&1
	@echo "$(GREEN)minilibx compiled$(RESET)"

clean:
	@make clean -C $(LIBFT_DIR) -s
	@make clean -C $(MLX_DIR) -s
	@rm -rf $(OBJS_DIR)
	@echo "$(PURPLE)clean successful$(RESET)"

fclean: clean
	@clear
	@make fclean -C $(LIBFT_DIR) -s
	@rm -f $(NAME)
	@echo "$(PURPLE)fclean successful$(RESET)"

clear:
	@clear

re: clear fclean all

test:
	./so_long assets/maps/valid_bonus/map_valid_big.ber

val:
	valgrind ./so_long assets/maps/valid_bonus/map_valid_2.ber

seg:
	valgrind --tool=memcheck --track-origins=yes --error-exitcode=1 --leak-check=no ./so_long assets/maps/valid_bonus/map_valid_2.ber

FORCE:

.PHONY: all clean fclean re

# # NAME
# NAME = so_long

# # SOURCE FILES
# SRCS	= main.c \
# 		  map_loader.c \
# 		  input_handler.c \
# 		  game_loop.c \
# 		  render.c \
# 		  validation.c

# # LIBFT
# LIBFT_DIR = libft
# LIBFT	= ${LIBFT_DIR}/libft.a

# # OBJECTS
# OBJS	=  ${addprefix ./, ${SRCS:.c=.o}}

# # INCLUDES
# INCLUDES	= -I minilibx_linux -I ./ -I ${LIBFT_DIR}

# # COMPILER & FLAGS
# AR		= ar rcs
# RM		= rm -f
# GCC		= gcc
# CFLAGS	= -Wall -Werror -Wextra

# # MINILIBX
# MLXFLAG		= -lmlx -lXext -lX11 -L/usr/lib -lm
# #MLX_MACOS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# # MLX_LINUX	= -L minilibx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)

# # MAKE & BUILD
# all: ${LIBFT} ${NAME}

# ${LIBFT}:
# 	make -C ${LIBFT_DIR}

# $(NAME): $(OBJS)
# #	$(CC) $(OBJS) ${MLX_MACOS}
# 	$(GCC) $(OBJS) ${MLXFLAG}

# %.o: src/%.c
# 	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@
# #	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ # MACOS
# 	$(GCC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# # CLEANING
# clean:
# 	${RM} 
# 	make -C ${LIBFT_DIR} clean

# fclean:	clean
# 	${RM} 
# 	make -C ${LIBFT_DIR} clean

# re:	fclean all

# .PHONY:	all clean fclean re