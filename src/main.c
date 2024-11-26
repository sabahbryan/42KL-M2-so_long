/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:55 by bryaloo           #+#    #+#             */
/*   Updated: 2024/11/19 17:30:43 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Function prototypes
int	init_game(t_game *game, char *map_file);

/**
 * @brief	Main function to initialise the game and start the game loop
 * @param	argc	Number of command line arguments
 * @param	argv	Array of command line arguments (map file path)
 * @var		game	pointer to the game structure
 * @return	1) prints error message if argument count is not 2
 * @return	2) 
 * @return	3)
 * @note	1) If the number of arguments is not 2, print usage message
 * @note	2) calls init_game function to initialise the game
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./so_long <map_file.ber>\n"));
	if (!init_game(&game, argv[1]))
		return (1);
	mlx_loop(game.mlx);
	return (0);
}

/**
 * @brief	Initialise the game window and load the map
 * @param	game	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
int	init_game(t_game *game, char *map_file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("Error\nFailed to initialize MiniLibX.\n"));
	game->map = load_map(map_file);
	if (!game->map)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	if (!game->win)
		return (print_error("Error\nFailed to create window.\n"));
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	return (1);
}

void	load_player_images(t_game *game)
{
    game->player_up_img = mlx_xpm_file_to_image(game->mlx, "player_up.xpm", 
                                                &width, &height);
    game->player_down_img = mlx_xpm_file_to_image(game->mlx, "player_down.xpm", 
                                                  &width, &height);
    game->player_left_img = mlx_xpm_file_to_image(game->mlx, "player_left.xpm", 
                                                  &width, &height);
    game->player_right_img = mlx_xpm_file_to_image(game->mlx, "player_right.xpm", 
                                                   &width, &height);
    if (!game->player_up_img || !game->player_down_img || 
        !game->player_left_img || !game->player_right_img)
        end_game(game, "Error: Failed to load player images.\n");
}

/**
 * @brief	Cleanly close the game and free resources
 * @param	game	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
int	close_game(t_game *game, char *message)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
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