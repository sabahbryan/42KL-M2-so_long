/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:17 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/12 16:25:29 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	{
		ft_printf("Error\nCould not open map file.\n");
		return (NULL);
	}
	map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (!map)
	{
		ft_printf("Error\nMemory allocation failed.\n");
		close(fd);
		return (NULL);
	}
	i = 0;
	while (i < MAX_MAP_HEIGHT)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		if (ft_strrchr(map[i], '\n'))
			map[i][ft_strlen(map[i]) - 1] = '\0';
		i++;
	}
	close(fd);
	printf("load_map_1\n"); //Test
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
	int	player_x;
	int	player_y;

	printf("validate_map_1\n"); //Test
	if (!map || !check_rectangular(map) || !check_boundary_walls(map))
		return (0);
	printf("validate_map_2\n"); //Test
	width = ft_strlen(map[0]);
	height = calculate_map_height(map);
	printf("validate_map_3\n"); //Test
	if (!has_required_elements(map, width, height))
		return (0);
	printf("validate_map_4\n"); //Test
	// Find the player's position dynamically
	if (!find_player_position(map, &player_x, &player_y))
		return (0); // Player not found, invalid map
	return (check_path(map, width, height, player_x, player_y)); //find player
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
	printf("check_rectangular_1\n"); //Test
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			return (0);
		printf("check_rectangular_2\n"); //Test
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

	printf("check_boundary_walls_1\n"); //Test
	// Check if map exists and is valid
	if (!map || !map[0])
		return (0);

	printf("check_boundary_walls_2\n"); //Test
	width = ft_strlen(map[0]);
	height = calculate_map_height(map);

	// Ensure the map has at least 2 rows and 2 columns
	if (height < 2 || width < 2)
		return (0);

	i = 0;
	printf("check_boundary_walls_3\n"); //Test
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (0);
		i++;
	}
	printf("check_boundary_walls_4\n"); //Test
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	printf("check_boundary_walls_5\n"); //Test
	return (1);
}

/**
 * @brief	checks if the given map contains 1 of each element 
 * @param	map	 2D map array
 * @param	width	number of columns in the map
 * @param	height	number of rows in the map
 * @var		x	iterates through each column
 * @var		y	iterates through each row
 * @var		player	counts the number of players (should only be 1)
 * @var		exit	counts the number of exits (should only be 1)
 * @var		collectible	Counts occurrences of 'C'
 * @return	if conditions are satisfied, otherwise returns 0
 * @note	1) initialise all counters to 0 before counting the elements
 * @note	2) loops through rows of the map (indexed by y)
 * @note	3) loops through columns of the map (indexed by x)
 * @note	4) increments counters (P, E, C) if respective element is found
 * @note	5) returns 1 if conditions are satisfied
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
	printf("has_required_elements_1\n"); //Test
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

	printf("calculate_map_height_1\n"); //Test
	// Safeguard against null map
	if (!map)
		return (0);

	printf("calculate_map_height_2\n"); //Test
	height = 0;
	while (map[height])
		height++;
	return (height);
}

/**
 * @brief	Frees the allocated memory for the map
 * @param	map	 2D map array
 * @param	height	 number of rows in the map
 * @var		i	counter to iterate through each row
 * @return	if map is NULL, returns to prevent freeing invalid pointer
 * @note	1) loops through each row
 * @note	2) calls free if map is not NULL to deallocate memory
 * @note	3) frees map pointer after all rows are freed
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