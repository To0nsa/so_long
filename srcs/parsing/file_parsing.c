/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:11:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:57:21 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file_type(t_game *game, t_map *map)
{
	size_t	len;

	len = ft_strlen(map->filename);
	if (len < 4 || ft_strncmp(map->filename + len - 4, ".ber", 4) != 0)
		map_error(game, "Error\nFile sould .ber extension\n", map);
}

void	open_map(t_game *game, t_map *map)
{
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
	{
		perror("Error\nopening file in open_map");
		free_all(game);
		exit(EXIT_FAILURE);
	}
}

void	read_map(t_game *game, t_map *map)
{
	char	*temp;

	map->line = get_next_line(map->fd);
	while (map->line != NULL)
	{
		temp = map->file;
		map->file = ft_strjoin(map->file, map->line);
		if (map->file == NULL)
		{
			if (temp != NULL)
				free(temp);
			free_all(game);
			perror("Error\nft_strjoin failed in map_parser");
			exit(EXIT_FAILURE);
		}
		if (temp != NULL)
			free(temp);
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	if (errno == ENOMEM)
	{
		perror("Error\nget_next_line failed in map_parser");
		fail_close_game(game);
	}
}

void	close_map(t_game *game, t_map *map)
{
	if (close(map->fd) == -1)
	{
		perror("Error\nclosing file in close_map");
		free_all(game);
		exit(EXIT_FAILURE);
	}
}

void	create_map_matrix(t_game *game, t_map *map)
{
	map->matrix = ft_split(map->file, '\n');
	map->temp_matrix = ft_split(map->file, '\n');
	if (map->matrix == NULL || map->temp_matrix == NULL)
	{
		if (map->temp_matrix != NULL)
			ft_free_array_size((void **)map->temp_matrix, map->size.y);
		free(map->file);
		perror("Error\nft_split failed in create_map_matrix");
		free_all(game);
		exit(EXIT_FAILURE);
	}
	free(map->file);
	map->size.x = ft_strlen(map->matrix[0]);
	while (map->matrix[map->size.y] != NULL)
		map->size.y++;
}
