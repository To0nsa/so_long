/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:31:03 by nlouis            #+#    #+#             */
/*   Updated: 2024/11/26 16:43:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	calculate_drawing_pos(t_game *game, t_point element_pos, t_point vp_pos)
{
	t_point	drawing_pos;

	drawing_pos.x = (element_pos.x - vp_pos.x) * game->img.size.x;
	drawing_pos.y = (element_pos.y - vp_pos.y) * game->img.size.y;
	return (drawing_pos);
}

void	update_animation(t_img *img)
{
	clock_t	current_time;

	current_time = clock();
	if (current_time - img->exit.last_update >= img->exit.frame_delay)
	{
		img->exit.frame = (img->exit.frame + 1) % img->exit.frame_count;
		img->exit.last_update = current_time;
	}
	if (current_time - img->player.last_update >= img->player.frame_delay)
	{
		img->player.frame = (img->player.frame + 1) % img->player.frame_count;
		img->player.last_update = current_time;
	}
	if (current_time - img->player_hit.last_update
		>= img->player_hit.frame_delay)
	{
		img->player_hit.frame = (img->player_hit.frame + 1)
			% img->player_hit.frame_count;
		img->player_hit.last_update = current_time;
	}
	if (current_time - img->enemy.last_update >= img->enemy.frame_delay)
	{
		img->enemy.frame = (img->enemy.frame + 1) % img->enemy.frame_count;
		img->enemy.last_update = current_time;
	}
}
