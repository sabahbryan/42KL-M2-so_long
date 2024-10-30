/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:05:06 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/30 23:05:32 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Function prototypes
int		check_boundary_walls(char **map);
int		check_rectangular(char **map);

// Flood fill to check map accessibility
void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (game->map[y][x] == '1' || game->map[y][x] == 'F')
		return ;
	game->map[y][x] = 'F';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

// Display error messages and exit
void	*print_error(char *message)
{
	ft_putstr_fd(message, 2);
	return (NULL);
}
