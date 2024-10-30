/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:38 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/30 23:03:28 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Function prototypes
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y);

// Render the entire map
void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}

// Render a single tile based on its type
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
