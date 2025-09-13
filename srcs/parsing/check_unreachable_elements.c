/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:12:36 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:57:33 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	scan_flood_starting_pos(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->matrix[y][x] == 'P')
			{
				map->flood_starting_pos.y = (int)y;
				map->flood_starting_pos.x = (int)x;
				break ;
			}
			x++;
		}
		y++;
	}
}

static void	fill_region(t_game *game, t_map *map, t_point current_pos)
{
	char	cell;
	t_point	next_pos;
	int		i;

	if (current_pos.y < 0 || current_pos.y >= map->size.y
		|| current_pos.x < 0 || current_pos.x >= map->size.x)
		return ;
	cell = map->temp_matrix[current_pos.y][current_pos.x];
	if (cell == WALL || cell == 'F')
		return ;
	map->temp_matrix[current_pos.y][current_pos.x] = 'F';
	i = 0;
	while (i < 4)
	{
		next_pos.x = current_pos.x + game->direction[i].x;
		next_pos.y = current_pos.y + game->direction[i].y;
		fill_region(game, map, next_pos);
		i++;
	}
}

static void	flood_fill(t_game *game, t_map *map)
{
	t_point	current_pos;

	current_pos = map->flood_starting_pos;
	fill_region(game, map, current_pos);
}

static void	check_unreachable_elements(t_game *game, t_map *map)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			cell = map->temp_matrix[y][x];
			if (cell == COIN)
				map->unreachable_coin++;
			else if (cell == EXIT)
				map->unreachable_exit++;
			x++;
		}
		y++;
	}
	if (map->unreachable_coin > 0 || map->unreachable_exit > 0)
		map_error(game, "Error\nMap has unreachable elements\n", map);
	ft_free_array_size((void **)map->temp_matrix, map->size.y);
}

void	validate_map_paths(t_game *game, t_map *map)
{
	scan_flood_starting_pos(map);
	flood_fill(game, map);
	check_unreachable_elements(game, map);
}
