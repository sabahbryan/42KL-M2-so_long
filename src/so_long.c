/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:55 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/17 17:23:04 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//Function prototypes
// int		init_game(t_game *game, char *map_file);
void	load_player_images(t_game *game);
int		close_game(t_game *game, char *message);

/**
 * @brief	Main function to initialise the game and start the game loop
 * @param	argc	Number of command line arguments
 * @param	argv	Array of command line arguments (map file path)
 * @var		game	pointer to the game structure
 * @return	1) prints error message if argument count is not 2
 * @return	2) returns 1 if game initialisation fails
 * @return	3) returns 0 if game initialisation is successful
 * @note	1) If the number of arguments is not 2, print usage message
 * @note	2) calls init_game function to initialise the game
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error, correct format: \"./so_long <map_file.ber>\"\n");
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		ft_printf("Error: Cannot initialise game\n");
		return (1);
	}
	game_loop(&game);
	return (0);
}

/**
 * @brief	Initialise the game window and load the map
 * @param	game	 	 Pointer to the game structure
 * @param	map_file	 Path to the map file
 * @return	1) returns error if MiniLibX initialisation fails
 * @return	2) returns error if map loading fails
 * @return	3) returns error if window creation fails
 * @return	4) returns 1 if game initialisation is successful
 * @note	1) initialises MiniLibX abd returns pointer to MLX instance
 * @note	2) loads specified map file and returns 2D array of the map
 * @note	3) calculates window dimensions based on map size and TILE_SIZE
 * @note	4) creates a new window with the calculated dimensions
 * @note	5) finds player's starting position and stores in the game struct
 * @note	6) calculates the number of collectibles in the map
 * @note	7) initialises player and exit data
 * @note	8) loads map and player images, then renders them in the window
 * @note	9) sets up keypress and close window hooks
 */
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

/**
 * @brief	Loads the player images in all directions
 * @param	game	 Pointer to the game structure
 * @return	none
 * @note	1) uses mlx_xpm_file_to_image to load the player images
 * @note	2) points to integers where MLX will store the image dimensions
 * @note	3) stores the loaded images in "game->player_<direction>_img"
 * @note	4) prints error message if any image fails to load
 */
void	load_player_images(t_game *game)
{
	game->player_up_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player_up.xpm", &game->img_width, &game->img_height);
	game->player_down_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player_down.xpm", &game->img_width, &game->img_height);
	game->player_left_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player_left.xpm", &game->img_width, &game->img_height);
	game->player_right_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player_right.xpm", &game->img_width, &game->img_height);
	if (!game->player_up_img || !game->player_down_img
		|| !game->player_left_img || !game->player_right_img)
		close_game(game, "Error: Failed to load player images.\n");
}

/**
 * @brief	Loads the map images
 * @param	game	 Pointer to the game structure
 * @return	none
 * @note	1) uses mlx_xpm_file_to_image to load the map images
 * @note	2) points to integers where MLX will store the image dimensions
 * @note	3) stores the loaded images in "game-><name>_img"
 * @note	4) initialises exit to be "closed"
 * @note	5) changes exit to "open" when the player collects all collectibles
 */
void	load_map_images(t_game *game)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"assets/wall.xpm", &game->img_width, &game->img_height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"assets/collectable.xpm", &game->img_width, &game->img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"assets/floor.xpm", &game->img_width, &game->img_height);
	game->exit_close_img = mlx_xpm_file_to_image(game->mlx,
			"assets/exit_close.xpm", &game->img_width, &game->img_height);
	game->exit_open_img = mlx_xpm_file_to_image(game->mlx,
			"assets/exit_open.xpm", &game->img_width, &game->img_height);
	game->exit_open = 0;
}

/**
 * @brief	Cleanly close the game and free resources
 * @param	game	 Pointer to the game structure
 * @param	message	 Message to print before exiting
 * @return	 returns 0 as default value after freeing resources and exiting
 * @note	1) use mlx_destroy_window to close the game window
 * @note	2) prints message if provided
 * @note	3) return isn't necessary but added for clarity
 */
int	close_game(t_game *game, char *message)
{
	mlx_destroy_image(game->mlx, game->player_up_img);
	mlx_destroy_image(game->mlx, game->player_down_img);
	mlx_destroy_image(game->mlx, game->player_left_img);
	mlx_destroy_image(game->mlx, game->player_right_img);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->collectible_img);
	mlx_destroy_image(game->mlx, game->exit_open_img);
	mlx_destroy_image(game->mlx, game->exit_close_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	if (message)
		ft_putstr_fd(message, 1);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
