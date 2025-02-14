/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:09 by bryaloo           #+#    #+#             */
/*   Updated: 2025/02/14 21:29:02 by bryaloo          ###   ########.fr       */
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
	//printf("Key pressed: %d\n", keycode);
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
	// for(size_t i = 0; game->map[i]; i++)
	// {
	// 	printf("@@%s\n", game->map[i]);
	// }
	printf("Collected:%d\nRemaining:%d\n",game->player_collected,game->collectibles);
	return (0);
}
//Handle moves

/**
 * @brief	Move the player to a new position
 * @param	game	Pointer to the game structure
 * @param	dx	change in x-coordinate
 * @param	dy	change in y-coordinate
 * @var		dest	stores value of tile at the destination coordinates
 * @var		new_x	player's new x-coordinate
 * @var		new_y	player's new y-coordinate
 * @return	1) returns if the new position is out of bounds (hit the wall)
 * @return	2) returns if player hits the wall
 * @note	1) computes new player position based on movement
 * @note	2) ensures player doesn't move outside the map
 * @note	3) if player hits wall, block movement and return
 * @note	4) if player collects a collectible, decrement collectibles
 * @note	5) if all collectibles are collected, open the exit
 * @note	6) if player reaches exit with all collectibles, end the game
 * @note	7) updates player position: old position to 0, new position to P
 * @note	8) increments the movement counter and print in the terminal
 * @note	9) calls draw_images to "refresh the entire game window"
 * @note	9) mlx_put_image_to_window: to draw the player's new position
 */
void	move_player(t_game *game, int dx, int dy)
{
	char	dest;
	int		new_x;
	int		new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	// if (new_x < 0 || new_x >= game->map_width || 
	// 	new_y < 0 || new_y >= game->map_height)
	// 	return ;
	dest = game->map[new_y][new_x];
	if (dest == '1')
		return ;
	if (dest == 'C')
		game->collectibles--;
	if (game->collectibles == 0 && !game->exit_open)
		game->exit_open = 1;
	if (dest == 'E' && game->collectibles == 0)
		close_game(game, "Congratulations! You won!\n");
	if (dest == 'E' && game->collectibles != 0)
		return ;
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++; // initialize it?
	ft_printf("Moves: %d\n", game->moves);
	//ft_printf("player x %d\n", game->player_x);

	// draw_images(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->player_img,
	// 						new_x * 64, new_y * 64);
}

// static void    move_leftside(t_game *game, int player_x, int player_y)
// {
//     if (game->map[player_y][player_x - 1] != '1' && game->map[player_y][player_x - 1] != 'E')
//     {
//         if (game->map[player_y][player_x - 1] == 'C')
//             game->collectibles--;
//         game->map[player_y][player_x - 1] = 'P';
//         game->map[player_y][player_x] = '0';
//         game->moves++;
//         ft_printf("MOVES: %d\n", game->moves);
//     }
//     if (game->map[player_y][player_x - 1] == 'E' && game->collectibles == 0)
//     {
//         game->moves++;
//         ft_printf("MOVES: %d\n", game->moves);
//         ft_printf("You won\n");
//         mlx_destroy_window(game->mlx, game->win);
//         exit(0);
//     }
// }