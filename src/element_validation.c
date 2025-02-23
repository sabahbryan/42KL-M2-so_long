/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:05:06 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/23 20:14:48 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
 * @note	4) checks if all elements were reached by flood_fill
 */
int	has_reached_all_elements(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
//printf("%s\n", map[y]); //Prints the map with 'F' filled

/**
 * @brief	Counts the number of players, exits, and collectibles in the map
 * @param	map	 2D map array
 * @param	width	 Number of columns in the map
 * @param	height	 Number of rows in the map
 * @param	counts	 Array to store counts of players, exits, and collectibles
 * @return	None
 */
static	void	count_elements(char **map, int width, int height, int *counts)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
				counts[0]++;
			else if (map[y][x] == 'E')
				counts[1]++;
			else if (map[y][x] == 'C')
				counts[2]++;
			x++;
		}
		y++;
	}
}

/**
 * @brief	Checks if the map contains the required elements
 * @param	map	 2D map array
 * @param	width	Number of columns in the map
 * @param	height	Number of rows in the map
 * @return	1) returns if conditions are satisfied
 * @return	2) conditions: at least 1 player, 1 exit, and 1 collectible
 * @note	1) calls count_elements to count the elements in the map
 * @note	2) counts[0] = player, counts[1] = exit, counts[2] = collectible
 */
int	has_required_elements(char **map, int width, int height)
{
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	count_elements(map, width, height, counts);
	return (counts[0] == 1 && counts[1] == 1 && counts[2] >= 1);
}

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
int	find_player_position(char **map, int *player_x, int *player_y)
{
	int	x;
	int	y;

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
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/** 
 * @brief	Counts the number of collectibles in the map
 * @param	map	 2D map array
 * @var		x	counter for the x-coordinate (column)
 * @var		y	counter for the y-coordinate (row)
 * @var		count	Stores the number of collectibles
 * @return	1) returns the number of collectibles in the map
 * @note	1) loops through each row until NULL
 * @note	2) loops through each column until '\0'
 * @note	3) increments the count if a collectible is found
*/
int	number_of_collectibles(char **map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
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
	return (count);
}

/** ORIGINAL FUNCTION
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
// int	has_required_elements(char **map, int width, int height)
// {
// 	int	x;
// 	int	y;
// 	int	player;
// 	int	exit;
// 	int	collectible;

// 	player = 0;
// 	exit = 0;
// 	collectible = 0;
// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (x < width)
// 		{
// 			if (map[y][x] == 'P')
// 				player++;
// 			else if (map[y][x] == 'E')
// 				exit++;
// 			else if (map[y][x] == 'C')
// 				collectible++;
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (player == 1 && exit >= 1 && collectible >= 1);
// }