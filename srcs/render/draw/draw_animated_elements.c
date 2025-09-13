/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_animated_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:42:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player(t_game *game, t_img *img)
{
	game->drawing_pos = calculate_drawing_pos
		(game, game->player.pos, game->vp_pos);
	mlx_put_image_to_window(game->mlx, game->window.ptr,
		img->player.frames[img->player.frame],
		game->drawing_pos.x, game->drawing_pos.y);
}

void	draw_player_hit(t_game *game, t_img *img)
{
	game->drawing_pos = calculate_drawing_pos
		(game, game->player.pos, game->vp_pos);
	mlx_put_image_to_window(game->mlx, game->window.ptr,
		img->player_hit.frames[img->player_hit.frame],
		game->drawing_pos.x, game->drawing_pos.y);
}

void	draw_exit(t_game *game, t_map *map, t_img *img)
{
	if (map->coin_count != 0)
		return ;
	if (is_within_vp(game->exit.pos, game->window.start, game->window.end))
	{
		game->drawing_pos = calculate_drawing_pos
			(game, game->exit.pos, game->vp_pos);
		mlx_put_image_to_window(game->mlx, game->window.ptr,
			img->exit.frames[img->exit.frame],
			game->drawing_pos.x, game->drawing_pos.y);
	}
}

void	draw_enemy(t_game *game, t_map *map, t_img *img)
{
	int	i;

	i = 0;
	while (i < map->enemy_count)
	{
		if (is_within_vp(game->enemy[i].pos, game->window.start,
				game->window.end))
		{
			game->drawing_pos = calculate_drawing_pos
				(game, game->enemy[i].pos, game->vp_pos);
			mlx_put_image_to_window(game->mlx, game->window.ptr,
				img->enemy.frames[img->enemy.frame],
				game->drawing_pos.x, game->drawing_pos.y);
		}
		i++;
	}
}
