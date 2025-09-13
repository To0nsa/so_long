/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_static_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:59:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_free_spaces(t_game *game, t_map *map, t_img *img)
{
	t_point	pos;

	pos.y = game->window.start.y;
	while (pos.y < game->window.end.y)
	{
		pos.x = game->window.start.x;
		while (pos.x < game->window.end.x)
		{
			if (map->matrix[pos.y][pos.x] == FREE
				|| (map->matrix[pos.y][pos.x] == EXIT
				&& map->coin_count != 0))
			{
				game->drawing_pos = calculate_drawing_pos
					(game, pos, game->vp_pos);
				mlx_put_image_to_window(game->mlx, game->window.ptr, img->free,
					game->drawing_pos.x, game->drawing_pos.y);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_walls(t_game *game, t_map *map, t_img *img)
{
	t_point	pos;

	pos.y = game->window.start.y;
	while (pos.y < game->window.end.y && pos.y < map->size.y)
	{
		pos.x = game->window.start.x;
		while (pos.x < game->window.end.x && pos.x < map->size.x)
		{
			if (map->matrix[pos.y][pos.x] == WALL)
			{
				game->drawing_pos = calculate_drawing_pos
					(game, pos, game->vp_pos);
				mlx_put_image_to_window(game->mlx, game->window.ptr, img->wall,
					game->drawing_pos.x, game->drawing_pos.y);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_collectibles(t_game *game, t_map *map, t_img *img)
{
	t_point	pos;

	pos.y = game->window.start.y;
	while (pos.y < game->window.end.y && pos.y < map->size.y)
	{
		pos.x = game->window.start.x;
		while (pos.x < game->window.end.x && pos.x < map->size.x)
		{
			if (map->matrix[pos.y][pos.x] == COIN)
			{
				game->drawing_pos = calculate_drawing_pos
					(game, pos, game->vp_pos);
				mlx_put_image_to_window(game->mlx, game->window.ptr, img->coin,
					game->drawing_pos.x, game->drawing_pos.y);
			}
			pos.x++;
		}
		pos.y++;
	}
}
