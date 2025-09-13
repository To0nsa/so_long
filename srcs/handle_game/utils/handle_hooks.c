/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_pause_message(t_game *game)
{
	t_point	pos;

	pos.x = game->window.size.x / 2;
	pos.y = game->window.size.y / 2;
	mlx_string_put(game->mlx, game->window.ptr, pos.x, pos.y,
		0xFFFFFF, "PAUSED");
}

static int	pause_game(t_game *game)
{
	game->is_paused = !game->is_paused;
	mlx_clear_window(game->mlx, game->window.ptr);
	if (game->is_paused)
		draw_pause_message(game);
	return (SUCCESS);
}

static int	keypress_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	else if (keycode == PAUSE)
		pause_game(game);
	else if (!game->is_paused && !game->player.hit)
	{
		if (keycode == UP)
			move_player(game, game->direction[0]);
		else if (keycode == RIGHT)
			move_player(game, game->direction[1]);
		else if (keycode == DOWN)
			move_player(game, game->direction[2]);
		else if (keycode == LEFT)
			move_player(game, game->direction[3]);
	}
	return (0);
}

static int	resize_and_focus_hook(t_game *game)
{
	if (!game->is_paused)
		pause_game(game);
	return (SUCCESS);
}

void	handle_event_hooks(t_game *game, t_window *window)
{
	mlx_hook(window->ptr, KEYPRESS, KEYPRESS_MASK, keypress_hook, game);
	mlx_hook(window->ptr, FOCUS_OUT, FOCUS_CHANGE_MASK,
		resize_and_focus_hook, game);
	mlx_hook(window->ptr, FOCUS_IN, FOCUS_CHANGE_MASK,
		resize_and_focus_hook, game);
	mlx_hook(window->ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		close_game, game);
	mlx_hook(window->ptr, CONFIGURE_NOTIFY, STRUCTURE_NOTIFY_MASK,
		resize_and_focus_hook, game);
}
