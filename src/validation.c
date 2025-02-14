/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:05:06 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/14 22:01:08 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
 * @note	4) sets the last element of the array to NULL
 */
char **copy_map(char **original_map, int height)
{
    char    **map_copy;
    int     i;

	printf("copy_map_1\n"); //Test
    map_copy = malloc(sizeof(char *) * (height + 1));
    if (!map_copy)
        return (NULL);
    i = 0;
    while (i < height)
    {
        map_copy[i] = ft_strdup(original_map[i]);
        if (!map_copy[i])
            return (NULL);
        i++;
    }
    map_copy[i] = NULL;
    return (map_copy);
}
// Helper function to copy the map
// Remember to handle freeing on error in the real code

/**
 * @brief	Flood fill to check map accessibility
 * @param	map		 2D map array
 * @param	map_width	 width of the map
 * @param	map_height	 height of the map
 * @param	x	 current x-coordinate
 * @param	y	 current y-coordinate
 * @return	1) returns if x or y are out of bounds
 * @return	2) returns if current tile is a wall (1) or visited (F)
 * @note	1) checks if x or y are out of bounds
 * @note	2) checks if current tile is a wall (1) or visited (F)
 * @note	3) marks the current tile as visited (F)
 * @note	4) recursively expands search to adjacent tiles
 */
void	flood_fill(char **map, int map_width, int map_height, int x, int y)
{
	//printf("flood_fill_1\n"); //Test
	if (x < 0 || x >= map_width || y < 0 || y >= map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, map_width, map_height, x + 1, y);
	flood_fill(map, map_width, map_height, x - 1, y);
	flood_fill(map, map_width, map_height, x, y + 1);
	flood_fill(map, map_width, map_height, x, y - 1);
}

/**
 * @brief	Checks if all elements were reached by the player
 * @param	map	 2D map array
 * @var		x	counter for the x-coordinate (column)
 * @var		y	counter for the y-coordinate (row)
 * @return	1) returns 0 if not all elements were reached
 * @return	2) returns 1 if all elements were reached
 * @note	1) iterates each row until NULL
 * @note	2) iterates each column until '\0'
 * @note	3) checks if there's at least one 'C' or 'E' remaining
 */
int has_reached_all_elements(char **map)
{
    int x;
	int y;

    y = 0;
	printf("has_reached_all_elements_1\n"); //Test
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
			//printf("%s\n", map[y]); //Prints the map with 'F' filled
            if (map[y][x] == 'C' || map[y][x] == 'E')
				 return (0);
            x++;
        }
        y++;
    }
	printf("has_reached_all_elements_2\n"); //Test
    return (1);
}
// Check if all collectibles and the exit were reached by flood_fill
// C is collectible, E is exit
// If any collectible or exit is unreached, path is invalid
// All required elements were reached

/**
 * @brief	Verifies valid path from player to collectables and exit
 * @param	map		 2D map array
 * @param	width	 map width
 * @param	height	 map height
 * @param	start_x	 player's starting x-coordinate
 * @param	start_y	 player's starting y-coordinate
 * @var		map_copy	?
 * @return	1) returns 0 if copying fails
 * @return	2) returns 0 if no valid path to all elements
 * @return	3) returns 1 if there's a valid path to all elements
 * @note	1) duplicates the map to prevent modifying the original map
 * @note	2) calls flood_fill to check if the player can reach all elements
 * @note	3) checks if all elements were reached by the player
 * @note	4) frees the copied map if any elements remains
 * @note	5) frees the copied map to prevent memory leaks
 */
int check_path(char** map, int width, int height, int start_x, int start_y)
{
	char	**map_copy;

	printf("check_path_1\n"); //Test
	map_copy = copy_map(map, height);
	if (!map_copy)
		return (0);

	printf("check_path_2 %i %i\n", start_x, start_y); //Test
	flood_fill(map_copy, width, height, start_x, start_y);
	printf("check_path_3\n"); //Test
	if (!has_reached_all_elements(map_copy))
	{
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

// 
/**
 * @brief	Function to find the player's position in the map
 * @param	map		pointer to the 2D map array
 * @param	player_x	pointer to the player's x-coordinate
 * @param	player_y	pointer to the player's y-coordinate
 * @var		x	loop counter for the x-coordinate (column)
 * @var		y	loop counter for the y-coordinate (row)
 * @return	1) if the player is found, returns to indicate player found
 * @return	2) if the player is not found, returns to indicate player not found
 * @note	1) loops through each row (y) until NULL
 * @note	2) loops through each column (x) until '\0'
 * @note	3) returns if player is found
 */
int find_player_position(char **map, int *player_x, int *player_y)
{
	int x;
	int	y;

	printf("find_player_position_1\n"); //Test
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				printf("find_player_position_2\n"); //Test
				return (1); // Player found
			}
			x++;
		}
		y++;
	}
	printf("find_player_position_3\n"); //Test
	return (0); // Player not found
}

int	number_of_collectibles(char **map)
{
    int x;
	int y;
	int	count;

    y		= 0;
	count	= 0;
	printf("number_of_collectibles_1\n"); //Test
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'C')
				count++;
            x++;
        }
        y++;
    }
	printf("number_of_collectibles_2\n"); //Test
    return (count);
}