/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:32:21 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/02 21:56:00 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
// errno.h, math.h
#include <mlx.h>           // MiniLibX library for graphics
#include <stdlib.h>        // Standard library functions (malloc, free, etc.)
#include <fcntl.h>         // File control options (open)
#include <unistd.h>        // UNIX standard functions (write, read, close)

// Constants for window dimensions
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Constants for key codes (modify based on your system's codes)
#define KEY_W 13           // Up
#define KEY_A 0            // Left
#define KEY_S 1            // Down
#define KEY_D 2            // Right
#define KEY_ESC 53         // ESC key to exit

// Game structure to hold all necessary data
typedef struct s_game {
	void	*mlx;           // MiniLibX pointer
	void	*win;           // Window pointer
	char	**map;          // 2D map array loaded from the .ber file
	int		map_width;      // Width of the map
	int		map_height;     // Height of the map
	int		player_x;       // Player x-coordinate
	int		player_y;       // Player y-coordinate
	int		collectibles; // Total collectibles in the map
	int		player_collected;   // Number of collected items by the player
	int		player_at_exit;     // Flag to check if player reached the exit
	int		moves;
	int		player_dir; // 0: up, 1: down, 2: left, 3: right
	int		img_width;      // Width of the loaded images
	int		img_height;     // Height of the loaded images
	void	*player_up_img;
	void	*player_down_img;
	void	*player_left_img;
	void	*player_right_img;
	void	*wall_img;
	void	*collectible_img;
	void	*exit_open_img;
	void	*exit_close_img;
	void	*floor_img;
	int		exit_open;	// 0 = closed, 1 = open
} t_game;

//***FUNCTION PROTOTYPES***

// map_loader.c
char	**load_map(char *filename);
int		validate_map(char **map);
int		check_rectangular(char **map);
int		check_boundary_walls(char **map);
int		has_required_elements(char **map, int width, int height);
int		map_height(char **map);

// main.c
int		init_game(t_game *game, char *map_file);
void	load_player_images(t_game *game);
void	load_map_images(t_game *game);
int		close_game(t_game *game, char *message);

// input_handler.c
int		handle_keypress(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);

// game_loop.c
void	game_loop(t_game *game);
int		update_game(t_game *game);

// render.c
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y);
void	draw_wall(t_game *game, int x, int y);
void	draw_collectible(t_game *game, int x, int y);
void	draw_exit(t_game *game, int x, int y);
void	draw_player(t_game *game, int x, int y);
void	draw_floor(t_game *game, int x, int y);

// validation.c
char	**copy_map(char **original_map, int height);
void	flood_fill(t_game *game, int x, int y);
int		has_reached_all_elements(char **map);
int		check_path(char** map, int start_x, int start_y);
void	*print_error(char *message);

#endif

/*struct
	player
	map height/width
	wall
	collectable
	exit
	empty_floor
 */

/*
	src functions here
 */