/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:55 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/08 18:25:57 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//Function prototypes
int		init_game(t_game *game, char *map_file);
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
		print_error("Usage: ./so_long <map_file.ber>\n");
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		print_error("Error: Cannot initialise game\n");
		return (1);
	}
	mlx_loop(game.mlx);
	return (0);
}

/**
 * @brief	Initialise the game window and load the map
 * @param	game	 	 Pointer to the game structure
 * @param	map_file	 Path to the map file
 * @return	1) prints error message if MiniLibX initialisation fails
 * @return	2) returns 0 if map loading fails
 * @return	3) prints error message if window creation fails
 * @return	4) returns 1 if game initialisation is successful
 * @note	?
 */
int	init_game(t_game *game, char *map_file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Error\nFailed to initialize MiniLibX.\n");
		return (0);
	}
	game->map = load_map(map_file);
	if (!game->map)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	if (!game->win)
	{
		print_error("Error\nFailed to create window.\n");
		return (0);
	}
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	return (1);
}

/**
 * @brief	?
 * @param	game	 Pointer to the game structure
 * @return	none
 * @note	?
 */
void	load_player_images(t_game *game)
{
	game->player_up_img = mlx_xpm_file_to_image(game->mlx,
		"player_up.xpm", &game->img_width, &game->img_height);
	game->player_down_img = mlx_xpm_file_to_image(game->mlx,
		"player_down.xpm", &game->img_width, &game->img_height);
	game->player_left_img = mlx_xpm_file_to_image(game->mlx,
		"player_left.xpm", &game->img_width, &game->img_height);
	game->player_right_img = mlx_xpm_file_to_image(game->mlx,
		"player_right.xpm", &game->img_width, &game->img_height);
	if (!game->player_up_img || !game->player_down_img || 
		!game->player_left_img || !game->player_right_img)
		close_game(game, "Error: Failed to load player images.\n");
}
//&width, &height);

/**
 * @brief	?
 * @param	game	 Pointer to the game structure
 * @return	none
 * @note	?
 */
void	load_map_images(t_game *game)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
		"wall.xpm", &game->img_width, &game->img_height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
		"collectible.xpm", &game->img_width, &game->img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
		"floor.xpm", &game->img_width, &game->img_height);
	game->exit_close_img = mlx_xpm_file_to_image(game->mlx,
		"exit_close.xpm", &game->img_width, &game->img_height);
	game->exit_open_img = mlx_xpm_file_to_image(game->mlx,
		"exit_open.xpm", &game->img_width, &game->img_height);
	game->exit_open = 0;
}
// Initialize as closed

/**
 * @brief	Cleanly close the game and free resources
 * @param	game	 Pointer to the game structure
 * @param	message	 ?
 * @return	 returns 0 as default value after freeing resources and exiting
 * @note	?
 */
int	close_game(t_game *game, char *message)
{
	mlx_destroy_window(game->mlx, game->win);
	//free_map(game->map);
	if (message)
		ft_putstr_fd(message, 1);
	exit(0);
	return (0);
}
/*{
	// Optional message display
	if (message)
		ft_printf("%s", message);

	// Cleanup resources
	free_map(game->map);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	
	// Exit the game
	exit(0);
}*/
/*{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(0);
	return (0);
}*/