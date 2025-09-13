/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_patrol_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:04:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:25:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_patrol_point_valid(t_game *game, t_point pos)
{
	if (pos.y < 0 || pos.y >= game->map.size.y
		|| pos.x < 0 || pos.x >= game->map.size.x)
		return (false);
	if (game->map.matrix[pos.y][pos.x] != FREE)
		return (false);
	return (true);
}

static bool	is_patrol_point_unique(t_enemy *enemy, int count, t_point pos)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (enemy->patrol_pts[i].x == pos.x && enemy->patrol_pts[i].y == pos.y)
			return (false);
		i++;
	}
	return (true);
}

static t_point	generate_random_point(t_point pos, int range)
{
	t_point	new_point;

	new_point.x = pos.x + (rand() % (2 * range + 1)) - range;
	new_point.y = pos.y + (rand() % (2 * range + 1)) - range;
	return (new_point);
}

static void	randomize_patrol_points(t_enemy *enemy, t_game *game, int range)
{
	int		count;
	t_point	pos;

	count = 0;
	while (count < enemy->patrol_pts_count)
	{
		pos = generate_random_point(enemy->pos, range);
		if (is_patrol_point_valid(game, pos)
			&& is_patrol_point_unique(enemy, count, pos))
		{
			enemy->patrol_pts[count] = pos;
			count++;
		}
	}
}

void	initialize_enemies_patrol_pts(t_enemy *enemy, t_game *game)
{
	int	i;

	srand(time(NULL));
	scan_enemies_pos(game, &game->map);
	i = 0;
	while (i < game->map.enemy_count)
	{
		enemy[i].patrol_pts_count = 4;
		randomize_patrol_points(&enemy[i], game, PATROL_RANGE);
		i++;
	}
}
