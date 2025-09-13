/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:37:30 by toonsa            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_player_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;
	int		i;

	i = 0;
	size = (t_point){img->size.x, img->size.y};
	img->player.frames = malloc(sizeof(void *) * 5);
	if (!img->player.frames)
		perror_free_and_exit("Error\nMalloc failed for player frames", game);
	img->player.frames[0] = mlx_xpm_file_to_image(mlx, PLAYER1_IMG,
			&size.x, &size.y);
	img->player.frames[1] = mlx_xpm_file_to_image(mlx, PLAYER2_IMG,
			&size.x, &size.y);
	img->player.frames[2] = mlx_xpm_file_to_image(mlx, PLAYER3_IMG,
			&size.x, &size.y);
	img->player.frames[3] = mlx_xpm_file_to_image(mlx, PLAYER4_IMG,
			&size.x, &size.y);
	img->player.frames[4] = mlx_xpm_file_to_image(mlx, PLAYER5_IMG,
			&size.x, &size.y);
	while (i < 5)
	{
		if (img->player.frames[i] == NULL)
			perror_free_and_exit("Error\nmlx_xpm_file_to_img()failed\n", game);
		i++;
	}
}

void	load_player_hit_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;
	int		i;

	i = 0;
	size = (t_point){img->size.x, img->size.y};
	img->player_hit.frames = malloc(sizeof(void *) * 3);
	if (!img->player_hit.frames)
		perror_free_and_exit("Error\nMalloc failed for player_hit frames", game);
	img->player_hit.frames[0] = mlx_xpm_file_to_image(mlx, PLAYER_HIT1,
			&size.x, &size.y);
	img->player_hit.frames[1] = mlx_xpm_file_to_image(mlx, PLAYER_HIT2,
			&size.x, &size.y);
	img->player_hit.frames[2] = mlx_xpm_file_to_image(mlx, PLAYER_HIT3,
			&size.x, &size.y);
	while (i < 3)
	{
		if (img->player_hit.frames[i] == NULL)
			perror_free_and_exit("Error\nmlx_xpm_file_to_img() failed\n", game);
		i++;
	}
}

void	load_images(t_game *game)
{
	load_collectible_images(&game->img, game->mlx, game);
	load_wall_images(&game->img, game->mlx, game);
	load_free_space_images(&game->img, game->mlx, game);
	load_exit_images(&game->img, game->mlx, game);
	load_enemy_images(&game->img, game->mlx, game);
	load_player_images(&game->img, game->mlx, game);
	load_player_hit_images(&game->img, game->mlx, game);
}
