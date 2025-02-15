/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:19:49 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/15 23:22:43 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
/**
* @brief	Flood fill to check map accessibility
* @param	map_info	pointer to t_map_info struct
* @param	x	 		current x-coordinate
* @param	y	 		current y-coordinate
* @return	1) returns if x or y are out of bounds
* @return	2) returns if current tile is a wall (1) or visited (F)
* @note	1) checks if x or y are out of bounds
* @note	2) checks if current tile is a wall (1) or visited (F)
* @note	3) marks the current tile as visited (F)
* @note	4) recursively expands search to adjacent tiles
*/
void	flood_fill(t_map_info *map_info, int x, int y)
{
	if (x < 0 || x >= map_info->width || y < 0 || y >= map_info->height)
		return ;
	if (map_info->map[y][x] == '1' || map_info->map[y][x] == 'F')
		return ;
	map_info->map[y][x] = 'F';
	flood_fill(map_info, x + 1, y);
	flood_fill(map_info, x - 1, y);
	flood_fill(map_info, x, y + 1);
	flood_fill(map_info, x, y - 1);
}

/**
* @brief	Verifies valid path from player to collectables and exit
* @param	map_info	pointer to t_map_info struct
* @param	start_x	 	player's starting x-coordinate
* @param	start_y	 	player's starting y-coordinate
* @var		map_copy	pointer to store a duplicate of the original map
* @return	1) returns 0 if copying fails
* @return	2) returns 0 if no valid path to all elements
* @return	3) returns 1 if there's a valid path to all elements
* @note	1) duplicates the map to prevent modifying the original map
* @note	2) calls flood_fill to check if the player can reach all elements
* @note	3) assigns values to the new map structure
* @note	4) checks if all elements were reached by the player
* @note	5) frees the copied map if any elements remains
* @note	6) frees the copied map to prevent memory leaks
*/
int	check_path(t_map_info *map_info, int start_x, int start_y)
{
	t_map_info	map_copy_info;
	char		**map_copy;

	map_copy = copy_map(map_info->map, map_info->height);
	if (!map_copy)
		return (0);
	map_copy_info.map = map_copy;
	map_copy_info.width = map_info->width;
	map_copy_info.height = map_info->height;
	flood_fill(&map_copy_info, start_x, start_y);
	if (!has_reached_all_elements(map_copy))
	{
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

// FORMER FUNCTION WITH 5 ARGUMENTS
// void	flood_fill(char **map, int map_width, int map_height, int x, int y)
// {
// 	if (x < 0 || x >= map_width || y < 0 || y >= map_height)
// 		return ;
// 	if (map[y][x] == '1' || map[y][x] == 'F')
// 		return ;
// 	map[y][x] = 'F';
// 	flood_fill(map, map_width, map_height, x + 1, y);
// 	flood_fill(map, map_width, map_height, x - 1, y);
// 	flood_fill(map, map_width, map_height, x, y + 1);
// 	flood_fill(map, map_width, map_height, x, y - 1);
// }

// FORMER FUNCTION WITH 5 ARGUMENTS
// int	check_path(char **map, int width, int height, int start_x, int start_y)
// {
// 	char	**map_copy;

// 	map_copy = copy_map(map, height);
// 	if (!map_copy)
// 		return (0);
// 	flood_fill(map_copy, width, height, start_x, start_y);
// 	if (!has_reached_all_elements(map_copy))
// 	{
// 		free_map(map_copy);
// 		return (0);
// 	}
// 	free_map(map_copy);
// 	return (1);
// }
