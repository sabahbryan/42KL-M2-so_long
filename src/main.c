/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:55 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/30 23:04:44 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Function prototypes
int	init_game(t_game *game, char *map_file);

// Main function to initialize the game and start the game loop
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

// Initialize the game window and load the map
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
