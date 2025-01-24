/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:05:06 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/24 16:43:15 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/**
 * @brief	?
 * @param	original_map	?
 * @param	height	?
 * @var		map_copy	?
 * @var		i	?
 * @return	?
 * @note	?
 */
char **copy_map(char **original_map, int height)
{
    char    **map_copy;
    int     i;

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
 * @param	game	?
 * @param	x	?
 * @param	y	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
void	flood_fill(char **map, int map_width, int map_height, int x, int y)
{
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
/*
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
*/

/**
 * @brief	?
 * @param	map	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
int has_reached_all_elements(char **map)
{
    int x;
	int y;

    y = 0;
	printf("16\n"); //Test
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
	printf("17\n"); //Test
    return (1);
}
// Check if all collectibles and the exit were reached by flood_fill
// C is collectible, E is exit
// If any collectible or exit is unreached, path is invalid
// All required elements were reached

/**
 * @brief	?
 * @param	game	?
 * @param	start_x	?
 * @param	start_y	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
int check_path(char** map, int width, int height, int start_x, int start_y)
{
	char	**map_copy;

	printf("13\n"); //Test
	map_copy = copy_map(map, height);
	if (!map_copy)
		return (0);

	printf("14 %i %i\n", start_x, start_y); //Test
	flood_fill(map_copy, width, height, start_x, start_y);
	printf("15\n"); //Test
	if (!has_reached_all_elements(map_copy))
	{
		free_map(map_copy, height);
		return (0);
	}
	free_map(map_copy, height);
	return (1);
}
/*
int check_path(t_game *game, int start_x, int start_y)
{
    char    **map_copy;

    map_copy = copy_map(game->map, game->map_height);
    if (!map_copy)
        return (0);

    flood_fill(game, start_x, start_y);
    if (!has_reached_all_elements(map_copy))
    {
        free_map(map_copy, game->map_height);
        return (0);
    }
    free_map(map_copy, game->map_height);
    return (1);
}
*/
// Main path-checking function
// Error handling for memory allocation failure
// Run flood_fill starting from player's position
// Check if all collectibles and the exit were marked (reached)
// free the copied map
// Path check failed
// free the copied map
// Path is valid

// Function to find the player's position in the map
int find_player_position(char **map, int *player_x, int *player_y)
{
	int x, y;

	printf("21\n"); //Test
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
				printf("22\n"); //Test
				return (1); // Player found
			}
			x++;
		}
		y++;
	}
	printf("23\n"); //Test
	return (0); // Player not found
}

/**
 * @brief	Displays error messages and exit
 * @param	game	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
void	*print_error(char *message)
{
	ft_putstr_fd(message, 2);
	return (NULL);
}

