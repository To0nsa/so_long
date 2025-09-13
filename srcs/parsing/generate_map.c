/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:45:45 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	generate_map(t_game *game, t_map *map)
{
	check_file_type(game, map);
	open_map(game, map);
	read_map(game, map);
	close_map(game, map);
	create_map_matrix(game, map);
	check_walls(game, map);
	check_shape(game, map);
	count_elements(game, map);
	check_elements(game, map);
	validate_map_paths(game, map);
}
