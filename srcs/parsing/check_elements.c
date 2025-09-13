/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 01:54:07 by toonsa            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls(t_game *game, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->size.x)
	{
		if (map->matrix[0][x] != WALL)
			map_error(game, "Error\nTop wall is not fully enclosed\n", map);
		if (map->matrix[map->size.y - 1][x] != WALL)
			map_error(game, "Error\nBottom wall is not fully enclosed\n", map);
		x++;
	}
	y = 1;
	while (y < map->size.y - 1)
	{
		if (map->matrix[y][0] != WALL)
			map_error(game, "Error\nLeft wall is not fully enclosed\n", map);
		if (map->matrix[y][map->size.x - 1] != WALL)
			map_error(game, "Error\nRight wall is not fully enclosed\n", map);
		y++;
	}
}

void	check_shape(t_game *game, t_map *map)
{
	int		y;
	size_t	row_len;

	y = 0;
	row_len = ft_strlen(map->matrix[y]);
	y++;
	while (y < map->size.y)
	{
		if (ft_strlen(map->matrix[y]) != row_len)
			map_error(game, "Error\nMap should be rectangular\n", map);
		y++;
	}
}

void	count_elements(t_game *game, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->matrix[y][x] == PLAYER)
				map->player_count++;
			else if (map->matrix[y][x] == ENEMY)
				map->enemy_count++;
			else if (map->matrix[y][x] == COIN)
				map->coin_count++;
			else if (map->matrix[y][x] == EXIT)
				map->exit_count++;
			else if (map->matrix[y][x] == WALL || map->matrix[y][x] == FREE)
				;
			else
				map_error(game, "Error\nWrong element detected\n", map);
			x++;
		}
		y++;
	}
}

void	check_elements(t_game *game, t_map *map)
{
	if (map->player_count != 1)
		map_error(game, "Error\nThere should be only one player\n", map);
	if (map->exit_count != 1)
		map_error(game, "Error\nThere should be only one exit\n", map);
	if (map->coin_count < 1)
		map_error(game, "Error\nThere should be min one collectible\n", map);
}
