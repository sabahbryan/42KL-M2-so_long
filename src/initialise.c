/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:13:52 by bryaloo           #+#    #+#             */
/*   Updated: 2025/03/05 21:42:44 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/**
 * @brief	Initialises the MiniLibX (MLX) library to handle graphics
 * @param	game	 Pointer to the game structure
 * @return	1) returns 0 if initialisation fails
 * @return	2) returns 1 if initialisation passes
 * @note	1) initialises graphic environment
 * @note	2) setups connection between program and X server
 * @note	3) setups window system for rendering images
 * @note	4) returns valid pointer if initialisation succeeds
 */
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	return (1);
}

/**
 * @brief	Loads the game map from a file
 * @param	game	 	Pointer to the game structure
 * @param	map_file	string containing the map file name 
 * @return	1) returns 0 if map fails to load
 * @return	2) returns 1 if map is successfully loaded
 * @note	1) calls load_map to read map file and allocate memory to store it
 * @note	2) returns (char **map) and assign it to "game->map"
 * @note	3) if map fails, frees all display related resources
 * @note	4) manually frees malloc-ed memory
 */
int	init_map(t_game *game, char *map_file)
{
	game->map = load_map(map_file);
	if (!game->map)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	return (1);
}

/**
 * @brief	Initialises creation of game window
 * @param	game	 Pointer to the game structure
 * @var		win_width	stores width of game window
 * @var		win_height	stores height of game window
 * @return	1) returns 0 if an error occurs
 * @return	2) returns 1 if window has been successfully created
 * @note	1) calculates window size based on the map's dimensions
 * @note	2) modifies win_width and win_height by reference (&)
 * @note	3) calls MLX to create a new game window 
 * @note	4) if successful, return pointer to the created window
 * @note	5) if failed, frees all resources to prevent leaks
 */
int	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	window_dimensions(game->map, &win_width, &win_height);
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
	{
		free_map(game->map);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	return (1);
}

/**
 * @brief	Initialises player and map elements with their positions
 * @param	game	 Pointer to the game structure
 * @note	1) calls function to find and set player's starting position
 * @note	2) calculate number of collectibles, then returns the count
 * @note	3) set the number of collected items to zero
 * @note	4) 0 means player is not at the exit on start
 * @note	5) set the number of moves to zero
 * @note	6) set player's initial facing position (down)
 */
void	init_game_state(t_game *game)
{
	find_player_position(game->map, &game->player_x, &game->player_y);
	game->collectibles = number_of_collectibles(game->map);
	game->player_collected = 0;
	game->player_at_exit = 0;
	game->moves = 0;
	game->player_dir = 1;
}

//OLD INIT_GAME
/*
int	init_game(t_game *game, char *map_file)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->map = load_map(map_file);
	if (!game->map)
		return (0);
	window_dimensions(game->map, &win_width, &win_height);
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
		return (0);
	find_player_position(game->map, &game->player_x, &game->player_y);
	game->collectibles = number_of_collectibles(game->map);
	game->player_collected = 0;
	game->player_at_exit = 0;
	game->moves = 0;
	game->player_dir = 1;
	load_map_images(game);
	load_player_images(game);
	render_map(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	return (1);
}
*/