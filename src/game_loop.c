/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:25 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/30 23:05:08 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Function prototypes
void	render_map(t_game *game);
int		update_game(t_game *game);

// Main game loop: move player, update state, and render
void	game_loop(t_game *game)
{
	render_map(game);
	mlx_loop_hook(game->mlx, &update_game, game);
}

// Update the game state based on player actions
int	update_game(t_game *game)
{
	if (game->player_collected == game->total_collectibles
		&& game->player_at_exit)
	{
		close_game(game);
	}
	render_map(game);
	return (0);
}
