/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 02:14:19 by toonsa            #+#    #+#             */
/*   Updated: 2025/03/28 12:06:53 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	perror_free_and_exit(char *error_message, t_game *game)
{
	if (errno != 0)
		perror("Error");
	if (ft_putstr_fd(error_message, 2) == -1)
		perror("Error\nft_putsr_fd failed in perror_free_and_exit");
	close_game(game);
}

void	map_error(t_game *game, char *error_message, t_map *map)
{
	if (ft_putstr_fd(error_message, 2) == -1)
		perror("Error\nft_putsr_fd failed in map_error");
	ft_free_array_size((void **)map->temp_matrix, map->size.y);
	free_all(game);
	exit(EXIT_FAILURE);
}

int	close_game(t_game *game)
{
	free_all(game);
	exit(EXIT_SUCCESS);
}

void	fail_close_game(t_game *game)
{
	free_all(game);
	exit(EXIT_FAILURE);
}
