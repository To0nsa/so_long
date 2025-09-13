/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_positions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:55:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	scan_exit_pos(t_game *game, t_map *map)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			if (map->matrix[pos.y][pos.x] == EXIT)
			{
				game->exit.pos = pos;
				return ;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	scan_player_pos(t_game *game, t_map *map)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			if (map->matrix[pos.y][pos.x] == PLAYER)
			{
				game->player.pos = pos;
				return ;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	scan_enemies_pos(t_game *game, t_map *map)
{
	int		i;
	t_point	pos;

	i = 0;
	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			if (map->matrix[pos.y][pos.x] == ENEMY)
			{
				game->enemy[i].pos = pos;
				i++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	scan_positions(t_game *game)
{
	scan_player_pos(game, &game->map);
	scan_enemies_pos(game, &game->map);
	scan_exit_pos(game, &game->map);
}
