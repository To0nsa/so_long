/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:27:32 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:09:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_game(t_game *game)
{
	update_vp(game, &game->window);
	define_vp_boundaries(game, &game->window, &game->map);
	update_animation(&game->img);
	draw_free_spaces(game, &game->map, &game->img);
	draw_walls(game, &game->map, &game->img);
	draw_collectibles(game, &game->map, &game->img);
	draw_exit(game, &game->map, &game->img);
	draw_enemy(game, &game->map, &game->img);
	if (game->player.hit == 0)
		draw_player(game, &game->img);
	else
		draw_player_hit(game, &game->img);
	write_moves(game);
}
