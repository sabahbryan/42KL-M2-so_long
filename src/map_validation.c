/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:02:19 by bryaloo           #+#    #+#             */
/*   Updated: 2025/03/01 19:06:12 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/**
 * @brief	Validates map structure, boundaries, and required elements
 * @param	map	 2D array representing the map
 * @var		width	Stores the width of the first row
 * @var		height	Stores the height of the map
 * @return	1) returns 0 if the map is NULL, not rectangular or invalid walls
 * @return	2) returns 0 if the map doesn't contain the required elements
 * @return	3) returns 1 if the map has a valid path between start and exit
 * @note	1) checks if the map is NULL
 * @note	2) checks if the map rows are of equal width
 * @note	3) checks if the map is surrounded by walls (1s)
 * @note	4) checks width and height
 * @note	5) checks if the map contains the required items (player, exit..
 * @note	6) checks if there is a valid path between the player and the exit
 */
int	validate_map(char **map)
{
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	t_map_info	map_info;

	if (!map || !check_rectangular(map) || !check_boundary_walls(map))
		return (0);
	width = ft_strlen(map[0]);
	height = calculate_map_height(map);
	if (!has_required_elements(map, width, height))
		return (0);
	if (!find_player_position(map, &player_x, &player_y))
		return (0);
	map_info.map = map;
	map_info.width = width;
	map_info.height = height;
	return (check_path(&map_info, player_x, player_y));
	ft_printf("Valid map\n");
}
//return (check_path(map, width, height, player_x, player_y));

/**
 * @brief	Checks if the map is rectangular
 * @param	map	 2D array representing the map
 * @var		i	counter to iterate through each row
 * @var		width	Stores the width of the first row
 * @return	returns 0 if the rows have different widths
 * @return	returns 1 if all rows have the same width
 * @note	1) initialise width to the length of the first row
 * @note	2) iterates each row and checks if the width is the same
 */
int	check_rectangular(char **map)
{
	int		i;
	size_t	width;

	i = 0;
	width = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	Ensures the map is surrounded by walls (boundary check)
 * @param	map	 2D array representing the map
 * @var		i		counter to iterate through each row
 * @var		width	Stores width of the first row
 * @var		height	Stores the height of the map
 * @return	1) returns 0 if any element in the first or last row is not '1'
 * @return	2) returns 0 if any element in the first or last column is not '1'
 * @note	1) checks all elements in first and last row are '1'
 * @note	2) checks all elements in first and last column are '1'
 */
int	check_boundary_walls(char **map)
{
	int	i;
	int	width;
	int	height;

	if (!map || !map[0])
		return (0);
	width = ft_strlen(map[0]);
	height = calculate_map_height(map);
	if (height < 2 || width < 2)
		return (0);
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	Determines the height (number of rows) of the map
 * @param	map	 2D map array
 * @var		height	integer variable to store the number of rows counted
 * @return	1) returns 0 if the map is NULL
 * @return	2) returns the total number of rows counted
 * @note	1) checks if the map is NULL (no height), if so, returns 0
 * @note	2) initialise height to 0 before counting
 * @note	3) iterates through map array and counts each row (height)
 */
int	calculate_map_height(char **map)
{
	int	height;

	if (!map)
		return (0);
	height = 0;
	while (map[height])
		height++;
	return (height);
}

/**
 * @brief	Determines the dimensions of the game window
 * @param	map	 2D map array
 * @param	win_width	pointer to store the width of the window
 * @param	win_height	pointer to store the height of the window
 * @var		map_width	Stores the width of the map
 * @var		map_height	Stores the height of the map
 * @return	none
 * @note	1) use ft_strlen to calculate the width of the map
 * @note	2) use calculate_map_height to calculate the height of the map
 * @note	3) multiply both dimensions by TILE_SIZE to get the window size
 */
void	window_dimensions(char **map, int *win_width, int *win_height)
{
	int	map_width;
	int	map_height;

	map_width = ft_strlen(map[0]);
	map_height = calculate_map_height(map);
	*win_width = map_width * TILE_SIZE;
	*win_height = map_height * TILE_SIZE;
}
