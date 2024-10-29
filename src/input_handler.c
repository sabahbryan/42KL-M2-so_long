/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:09 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/29 23:04:13 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Handle keypress events
int handle_keypress(int keycode, t_game *game) {
    if (keycode == KEY_W)
        move_player(game, 0, -1);
    else if (keycode == KEY_S)
        move_player(game, 0, 1);
    else if (keycode == KEY_A)
        move_player(game, -1, 0);
    else if (keycode == KEY_D)
        move_player(game, 1, 0);
    else if (keycode == KEY_ESC)
        close_game(game);
    return (0);
}

// Cleanly close the game and free resources
int close_game(t_game *game) {
    mlx_destroy_window(game->mlx, game->win);
    free_map(game->map);
    exit(0);
    return (0);
}

