/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:09 by bryaloo           #+#    #+#             */
/*   Updated: 2025/01/24 19:45:59 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_player(t_game *game, int dx, int dy);

/**
 * @brief	Handle keypress events
 * @param	keycode	 Key code of the pressed key
 * @param	game	 Pointer to the game structure
 * @return	returns 0 as default value
 * @note	1) quits game if ESC key is pressed
 * @note	2) moves player up if W or UP key is pressed
 * @note	3) moves player down if S or DOWN key is pressed
 * @note	4) moves player left if A or LEFT key is pressed
 * @note	5) moves player right if D or RIGHT key is pressed
 */
int	handle_keypress(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_game(game, "Game exited.\n");
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	
	//if (keycode == KEY_W || keycode == KEY_S || 
    //    keycode == KEY_A || keycode == KEY_D)
    //    move_player(game, game->player_x + dx, game->player_y + dy);
	return (0);
}
//Handle moves

/**
 * @brief	Move the player to a new position
 * @param	game	?
 * @param	dx	?
 * @param	dy	?
 * @var		dest	stores value of tile at the destination coordinates
 * @var		new_x	?
 * @var		new_y	?
 * @return	?
 * @return	?
 * @note	?
 */
void	move_player(t_game *game, int dx, int dy)
{
	char	dest;
	int		new_x;
	int		new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (new_x < 0 || new_x >= game->map_width || 
		new_y < 0 || new_y >= game->map_height)
		return ;
	dest = game->map[new_y][new_x];
	if (dest == '1')
		return ;
	if (dest == 'C')
		game->collectibles--;
	if (game->collectibles == 0 && !game->exit_open)
		game->exit_open = 1;
	if (dest == 'E' && game->collectibles == 0)
		close_game(game, "Congratulations! You won!\n");
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);

	draw_images(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->player_img,
	// 	game->player_x * game->img_width, game->player_y * game->img_height);
	mlx_put_image_to_window(game->mlx, game->win, game->player_img,
							new_x * 64, new_y * 64);
}
// Moves the player if the destination tile is not a wall
// Don't move into walls
// Pick up collectible
// Exit if all collected
// Update map and player position
// Increment movement counter
