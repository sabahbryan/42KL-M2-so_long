/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:25 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/14 21:12:06 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// Function prototypes
int	update_game(t_game *game);

/**
 * @brief	Main game loop: move player, update state, and render
 * @param	game	 Pointer to the game structure
 * @var		none
 * @return	none
 * @note	1) Calls render_map to draw the map
 * @note	2) Calls mlx_loop_hook to update the game state
 */
void	game_loop(t_game *game)
{
	printf("game_loop_1\n"); //Test
	render_map(game);
	mlx_loop_hook(game->mlx, &update_game, game);
	mlx_loop(game->mlx);
}
//game->mlx: manages the graphics window
//&update_game: pointer to the update_game function
//game:Passed as a parameter to update_game

/**
 * @brief	Update the game state based on player actions
 * @param	game	 Pointer to the game structure
 * @var		none
 * @return	used by mlx_loop_hook to update the game state
 * @note	1) checks if player has all collectibles and reached the exit
 * @note	2) if true, calls close_game and display victory message
 * @note	3) calls render_map to redraw the map
 */
int	update_game(t_game *game)
{
	//printf("update_game_1\n"); //Test
	if (game->player_collected == game->collectibles && game->player_at_exit)
	{
		close_game(game, "YAY!\n");	
	}
	render_map(game);
	return (0);
}
//total collectibles?
//win message?