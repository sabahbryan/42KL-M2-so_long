/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:55 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/11 22:59:29 by bryaloo          ###   ########.fr       */
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
	//mlx_loop(game.mlx);
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
		ft_printf("Error\nFailed to initialize MiniLibX.\n");
		return (0);
	}
	printf("init_game_1\n"); //Test
	game->map = load_map(map_file);
	printf("init_game_2\n"); //Test
	if (!game->map)
		//ft_printf("Error\nFailed to load map.\n");
		return (0);
	printf("init_game_3\n"); //Test	
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window.\n");
		return (0);
	}

	// Initialize player position and other game variables
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->player_collected = 0;
	game->player_at_exit = 0;
	game->moves = 0;
	game->player_dir = 0; // Initial direction (up)

	load_map_images(game);
	load_player_images(game);
	draw_images(game);

	printf("init_game_4\n"); //Test	
	mlx_key_hook(game->win, handle_keypress, game);
	printf("init_game_5\n"); //Test	
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
	if (!game->player_up_img || !game->player_down_img || 
		!game->player_left_img || !game->player_right_img)
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
 * @brief	Draws the map by placing images on the window
 * @param	game	 Pointer to the game structure
 * @var		x	 Column index
 * @var		y	 Row index
 * @var		tile_size	 Size of each tile in pixels
 * @var		screen_x	 X-coordinate on the screen
 * @var		screen_y	 Y-coordinate on the screen
 * @return	none
 * @note	1) loops through each row (y) until the end of the map
 * @note	2) loops through each column (x) until the end of the row
 * @note	3) converts map coordinates to screen coordinates based on pixels
 * @note	4) draws image based on the tile type using mlx_put_image_to_window
 */
void	draw_images(t_game *game)
{
	int	x;
	int	y;
	int	tile_size = 32; // 32x32 pixels per tile
	int	screen_x;
	int	screen_y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			screen_x = x * tile_size;
			screen_y = y * tile_size;

			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
											screen_x, screen_y);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible_img,
											screen_x, screen_y);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor_img,
											screen_x, screen_y);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit_close_img,
											screen_x, screen_y);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player_down_img,
											screen_x, screen_y);
			x++;
		}
		y++;
	}
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
	mlx_destroy_window(game->mlx, game->win);
	//free_map(game->map);
	if (message)
		ft_putstr_fd(message, 1);
	exit(0);
	return (0);
}
