/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:38 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/15 18:32:18 by bryaloo          ###   ########.fr       */
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
