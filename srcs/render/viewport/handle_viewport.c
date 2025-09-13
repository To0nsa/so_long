/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:08:47 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:08:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_vp(t_game *game, t_window *window)
{
	game->vp_size = (t_point)
	{
		window->size.x / game->img.size.x,
		window->size.y / game->img.size.y
	};
	game->vp_pos.x = game->player.pos.x - game->vp_size.x / 2;
	game->vp_pos.y = game->player.pos.y - game->vp_size.y / 2;
	if (game->vp_pos.x < 0)
		game->vp_pos.x = 0;
	if ((game->vp_pos.x + game->vp_size.x) > game->map.size.x)
		game->vp_pos.x = game->map.size.x - game->vp_size.x;
	if (game->vp_pos.y < 0)
		game->vp_pos.y = 0;
	if ((game->vp_pos.y + game->vp_size.y) > game->map.size.y)
		game->vp_pos.y = game->map.size.y - game->vp_size.y;
	if (game->vp_pos.x < 0)
		game->vp_pos.x = 0;
	if (game->vp_pos.y < 0)
		game->vp_pos.y = 0;
}

void	define_vp_boundaries(t_game *game, t_window *window, t_map *map)
{
	window->start = (t_point){game->vp_pos.x, game->vp_pos.y};
	window->end = (t_point){game->vp_pos.x + game->vp_size.x,
		game->vp_pos.y + game->vp_size.y};
	if (window->end.x > map->size.x)
		window->end.x = map->size.x;
	if (window->end.y > map->size.y)
		window->end.y = map->size.y;
}

int	is_within_vp(t_point pos, t_point wind_start, t_point win_end)
{
	return (pos.x >= wind_start.x && pos.x < win_end.x
		&& pos.y >= wind_start.y && pos.y < win_end.y);
}
