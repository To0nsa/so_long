/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:50:44 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:26:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_player_hit(t_game *game, t_point new_pos, char target)
{
	t_point	adjacent;
	int		i;

	i = 0;
	while (i < 4)
	{
		adjacent.x = new_pos.x + game->direction[i].x;
		adjacent.y = new_pos.y + game->direction[i].y;
		if (game->map.matrix[adjacent.y][adjacent.x] == target)
		{
			if (!game->player.hit)
			{
				game->player.hit = 1;
				game->player.hit_timer = (clock() * 1000) / CLOCKS_PER_SEC;
				return (true);
			}
		}
		i++;
	}
	return (false);
}
