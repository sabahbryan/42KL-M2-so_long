/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:38 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/15 17:38:12 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/**
 * @brief	Renders the entire map by iterating through each tile
 * @param	game	 pointer to the game structure
 * @var		x	column index, x-coordinates
 * @var		y	rows index, y-coordinates
 * @return	none
 * @note	1) Iterates through each tile in the map starting from top row
 * @note	2) Continues iterating while row index y < total number of rows
 * @note	3) Resets the column index x to 0 for each row
 */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief	Renders a single tile based on its type
 * @param	game	 pointer to the game structure
 * @param	x	column index, x-coordinates
 * @param	y	row index, y-coordinates
 * @var		tile	Stores the type of tile at the given position
 * @return	none
 * @note	1) gets the tile type from the map array
 * @note	2) calls the appropriate draw function based on the tile type
 */
void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == '1')
		draw_wall(game, x, y);
	else if (tile == 'C')
		draw_collectible(game, x, y);
	else if (tile == 'E')
		draw_exit(game, x, y);
	else if (tile == 'P')
		draw_player(game, x, y);
	else
		draw_floor(game, x, y);
}

// Draws a wall tile at the specified position
void	draw_wall(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
}

// Draws a collectible tile at the specified position
void	draw_collectible(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
}

// Draws the exit tile at the specified position
// The exit_open flag is used to determine which exit image to draw
void	draw_exit(t_game *game, int x, int y)
{
	if (game->exit_open)
		mlx_put_image_to_window(game->mlx, game->win,
			game->exit_open_img, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->exit_close_img, x * TILE_SIZE, y * TILE_SIZE);
}

// Draws the player tile at the specified position
// The player direction is used to determine which player image to draw
// Default to the "right" image for rendering
void	draw_player(t_game *game, int x, int y)
{
	if (game->player_dir == 0)
		game->player_img = game->player_up_img;
	else if (game->player_dir == 1)
		game->player_img = game->player_down_img;
	else if (game->player_dir == 2)
		game->player_img = game->player_left_img;
	else
		game->player_img = game->player_right_img;
	mlx_put_image_to_window(game->mlx, game->win,
		game->player_img, x * TILE_SIZE, y * TILE_SIZE);
}

// Draws the floor tile at the specified position
void	draw_floor(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
}
