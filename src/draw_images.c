/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:30:26 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/15 18:31:07 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
