/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:25 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/03 17:05:35 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Function prototypes
void	game_loop(t_game *game);
int		update_game(t_game *game);

/**
 * @brief	Main game loop: move player, update state, and render
 * @param	game	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
void	game_loop(t_game *game)
{
	render_map(game);
	mlx_loop_hook(game->mlx, &update_game, game);
}

/**
 * @brief	Update the game state based on player actions
 * @param	game	?
 * @var		fd	?
 * @var		map	?
 * @var		i	?
 * @return	?
 * @note	?
 */
int	update_game(t_game *game)
{
	if (game->player_collected == game->collectibles //total collectibles?
		&& game->player_at_exit)
	{
		close_game(game, "EDIT MESSAGE\n");	//win message?
	}
	render_map(game);
	return (0);
}

