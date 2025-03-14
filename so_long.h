/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:32:21 by bryaloo           #+#    #+#             */
/*   Updated: 2025/03/07 17:04:17 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include "./minilibx_linux/mlx.h"           // MiniLibX library for graphics
# include <stdlib.h>        // Standard library functions (malloc, free, etc.)
# include <fcntl.h>         // File control options (open)
# include <unistd.h>        // UNIX standard functions (write, read, close)
# include "stdio.h" //just for testing

// Constants for window dimensions
// #define WIN_WIDTH 1440
// #define WIN_HEIGHT 720

// Constants for tile size
# define TILE_SIZE 32

// Constants for key codes (Linux)
# define KEY_W 119		// Up
# define KEY_A 97		// Left
# define KEY_S 115		// Down
# define KEY_D 100		// Right
# define KEY_ESC 65307	// ESC key to exit
# define KEY_UP 65362	// Up
# define KEY_LEFT 65361	// Left
# define KEY_DOWN 65364	// Down
# define KEY_RIGHT 65363	// Right

// // Constants for key codes (MacOS)
// #define KEY_W 13		// Up
// #define KEY_A 0			// Left
// #define KEY_S 1			// Down
// #define KEY_D 2			// Right
// #define KEY_ESC 53		// ESC key to exit
// #define KEY_UP 126		// Up
// #define KEY_LEFT 123	// Left
// #define KEY_DOWN 125	// Down
// #define KEY_RIGHT 124	// Right

// Game structure to hold all necessary data
typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		player_collected;
	int		player_at_exit;
	int		moves;
	int		player_dir;
	int		img_width;
	int		img_height;
	void	*player_img;
	void	*player_up_img;
	void	*player_down_img;
	void	*player_left_img;
	void	*player_right_img;
	void	*wall_img;
	void	*collectible_img;
	void	*exit_open_img;
	void	*exit_close_img;
	void	*floor_img;
	int		exit_open;
}	t_game;
// MiniLibX pointer
// Window pointer
// 2D map array loaded from the .ber file
// Player x-coordinate
// Player y-coordinate
// Total collectibles in the map
// Number of collected items by the player
// Flag to check if player reached the exit
// 0: up, 1: down, 2: left, 3: right
// Width of the loaded images
// Height of the loaded images
// Player image pointer
// 0 = closed, 1 = open

// Map information structure for flood_fill and check_path
typedef struct s_map_info
{
	char	**map;
	int		width;
	int		height;
	int		exit_reachable;
	int		total_c;
}	t_map_info;

//***FUNCTION PROTOTYPES***

// so_long.c (MAIN)
int		init_game(t_game *game, char *map_file);
void	load_player_images(t_game *game);
void	load_map_images(t_game *game);
int		close_game(t_game *game, char *message);
int		quit_game(t_game *game);
//quit_gamme to fix SEGFAULT

//initialise.c
int		init_mlx(t_game *game);
int		init_map(t_game *game, char *map_file);
int		init_window(t_game *game);
void	init_game_state(t_game *game);

// map_loader.c
//static	int	read_map_lines(int fd, char **map);
char	**load_map(char *filename);
char	**copy_map(char **original_map, int height);
void	free_map(char **map);

//map_validation.c
int		validate_map(char **map);
int		check_rectangular(char **map);
int		check_boundary_walls(char **map);
int		calculate_map_height(char **map);
void	window_dimensions(char **map, int *win_width, int *win_height);

// element_validation.c
int		has_reached_all_elements(char **map);
//int		check_e(char **map);
//static void count_elements(char **map, int width, int height, int *counts);
int		has_required_elements(char **map, int width, int height);
int		find_player_position(char **map, int *player_x, int *player_y);
int		number_of_collectibles(char **map);

// path_validation.c
int		count_collectibles(char **map);
void	flood_fill(t_map_info *map_info, int x, int y);
int		check_path(t_map_info *map_info, int start_x, int start_y);

// render.c
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y);

// draw_images.c
void	draw_wall(t_game *game, int x, int y);
void	draw_collectible(t_game *game, int x, int y);
void	draw_exit(t_game *game, int x, int y);
void	draw_player(t_game *game, int x, int y);
void	draw_floor(t_game *game, int x, int y);

// input_handler.c
int		handle_keypress(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);

// game_loop.c
void	game_loop(t_game *game);
int		update_game(t_game *game);

#endif
