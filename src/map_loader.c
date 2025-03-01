/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:17 by bryaloo           #+#    #+#             */
/*   Updated: 2025/03/01 19:13:31 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// Define MAX_MAP_HEIGHT with an appropriate value
#define MAX_MAP_HEIGHT 100 

/**
 * @brief	Reads lines from the map file and stores them in the map array
 * @param	fd	 File descriptor of the map file
 * @param	map	2D array to store the map
 * @var		i	 Iterator for the map array
 * @return	Number of lines read from the file
 */
static	int	read_map_lines(int fd, char **map)
{
	int	i;

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
	return (i);
}

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
 * @note	6) Frees map if validation fails
 */
char	**load_map(char *filename)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	read_map_lines(fd, map);
	close(fd);
	if (validate_map(map))
		return (map);
	free_map(map);
	return (NULL);
}

/**
 * @brief	Duplicates a copy of the original map
 * @param	original_map	 2D array of the original map
 * @param	height	 number of rows in the map
 * @var		map_copy	?
 * @var		i	?
 * @return	1) returns NULL if allocation fails
 * @return	2) returns NULL if copying fails
 * @return	3) returns the copied map if successful
 * @note	1) allocates memory for array of strings, plus one for '\0'
 * @note	2) duplicates each row (string) of original map
 * @note	2) create new memory block for each row in the map
 * @note	3) duplication to prevent modifying the original map
 * @note	4) frees previously malloc-ed rows and columns
 * @note	5) sets the last element of the array to NULL
 */
char	**copy_map(char **original_map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(original_map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[--i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
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
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// ORIGINAL FUNCTION
// char	**load_map(char *filename)
// {
// 	int		fd;
// 	char	**map;
// 	int		i;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
// 	if (!map)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < MAX_MAP_HEIGHT)
// 	{
// 		map[i] = get_next_line(fd);
// 		if (!map[i])
// 			break ;
// 		if (ft_strrchr(map[i], '\n'))
// 			map[i][ft_strlen(map[i]) - 1] = '\0';
// 		i++;
// 	}
// 	close(fd);
// 	if (validate_map(map))
// 		return (map);
// 	return (NULL);
// }