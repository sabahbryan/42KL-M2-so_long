/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:17 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/05 19:09:14 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Define MAX_MAP_HEIGHT with an appropriate value
#define MAX_MAP_HEIGHT 100 

// Function prototypes
// char	**load_map(char *filename);
// int		validate_map(char **map);
// int		check_rectangular(char **map);
// int		check_boundary_walls(char **map);

/**
 * @brief	Loads the map from a .ber file
 * @param	filename	 The name of the .ber file to load
 * @var		fd	file descriptor, to open the file
 * @var		map	2D array to store the map
 * @var		i	iterates through each line of the map
 * @return	1) print error message if the map is invalid
 * @return	2) print error message if malloc fails
 * @return	3) returns the map if it is valid, otherwise NULL
 * @note	1) Attempts to open the map file in read-only mode.
 * @note	2) Allocates memory for the map array.
 * @note	3) Reads each line of the map file and stores it in the map array.
 * @note	4) Closes the file descriptor after reading all lines.
 * @note	5) Validates the map structure.
 */
char	**load_map(char *filename)
{
	int		fd;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nCould not open map file.\n"));
	map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (!map)
		return (print_error("Error\nMemory allocation failed.\n"));
	i = 0;
	while (i < MAX_MAP_HEIGHT)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		i++;
	}
	close(fd);
	if (validate_map(map))
		return (map);
	return (NULL);
}

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
	int	width;
	int	height;

	if (!map || !check_rectangular(map) || !check_boundary_walls(map))
		return (0);
	width = ft_strlen(map[0]);
	height = calculate_map_height(map);
	if (!has_required_elements(map, width, height))
		return (0);
	return (check_path(map, width, height));
}

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

	width = ft_strlen(map[0]);
	height = calculate_map_height(map);
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	?
 * @param	map	?
 * @param	width	?
 * @param	height	?
 * @var		x	?
 * @var		y	?
 * @var		player	?
 * @var		exit	?
 * @var		collectible	?
 * @return	?
 * @note	?
 */
int	has_required_elements(char **map, int width, int height)
{
	int	x;
	int	y;
	int	player;
	int	exit;
	int	collectible;

	player = 0;
	exit = 0;
	collectible = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
				player++;
			else if (map[y][x] == 'E')
				exit++;
			else if (map[y][x] == 'C')
				collectible++;
			x++;
		}
		y++;
	}
	return (player == 1 && exit >= 1 && collectible >= 1);
}

#include "so_long.h"

/**
 * @brief	?
 * @param	map	?
 * @var		height	?
 * @return	?
 * @note	?
 */
int	calculate_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}
// Calculate the height of the map (number of rows)

/*
int	calculate_map_width(char **map)
{
	if (!map || !map[0])
		return (0);
	return (ft_strlen(map[0]));
}
// Replace ft_strlen with strlen if you're not using libft
*/

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}