/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:29:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_collectible_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;

	size = (t_point){img->size.x, img->size.y};
	img->coin = mlx_xpm_file_to_image(mlx, COIN_IMG, &size.x, &size.y);
	if (img->coin == NULL)
		perror_free_and_exit("Error\nmlx_xpm_file_to_image() failed\n", game);
}

void	load_free_space_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;

	size = (t_point){img->size.x, img->size.y};
	img->free = mlx_xpm_file_to_image(mlx, FREE_IMG, &size.x, &size.y);
	if (img->free == NULL)
		perror_free_and_exit("Error\nmlx_xpm_file_to_image() failed\n", game);
}

void	load_wall_images(t_img *img, void *mlx, t_game *game)
{
	img->wall = mlx_xpm_file_to_image(mlx, WALL_IMG, &img->size.x,
			&img->size.y);
	if (img->wall == NULL)
		perror_free_and_exit("Error\nmlx_xpm_file_to_image() failed\n", game);
}

void	load_exit_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;
	int		i;

	i = 0;
	size = (t_point){img->size.x, img->size.y};
	img->exit.frames = malloc(sizeof(void *) * 8);
	if (!img->exit.frames)
		perror_free_and_exit("Error\nMalloc failed for exit frames", game);
	img->exit.frames[0] = mlx_xpm_file_to_image(mlx, EXIT1, &size.x, &size.y);
	img->exit.frames[1] = mlx_xpm_file_to_image(mlx, EXIT2, &size.x, &size.y);
	img->exit.frames[2] = mlx_xpm_file_to_image(mlx, EXIT3, &size.x, &size.y);
	img->exit.frames[3] = mlx_xpm_file_to_image(mlx, EXIT4, &size.x, &size.y);
	img->exit.frames[4] = mlx_xpm_file_to_image(mlx, EXIT5, &size.x, &size.y);
	img->exit.frames[5] = mlx_xpm_file_to_image(mlx, EXIT6, &size.x, &size.y);
	img->exit.frames[6] = mlx_xpm_file_to_image(mlx, EXIT7, &size.x, &size.y);
	img->exit.frames[7] = mlx_xpm_file_to_image(mlx, EXIT8, &size.x, &size.y);
	while (i < 8)
	{
		if (img->exit.frames[i] == NULL)
			perror_free_and_exit("Error\nmlx_xpm_file_to_img() failed\n", game);
		i++;
	}
}

void	load_enemy_images(t_img *img, void *mlx, t_game *game)
{
	t_point	size;
	int		i;

	i = 0;
	size = (t_point){img->size.x, img->size.y};
	img->enemy.frames = malloc(sizeof(void *) * 5);
	if (!img->enemy.frames)
		perror_free_and_exit("Error\nMalloc failed for enemy frames", game);
	img->enemy.frames[0] = mlx_xpm_file_to_image(mlx, ENEM1, &size.x, &size.y);
	img->enemy.frames[1] = mlx_xpm_file_to_image(mlx, ENEM2, &size.x, &size.y);
	img->enemy.frames[2] = mlx_xpm_file_to_image(mlx, ENEM3, &size.x, &size.y);
	img->enemy.frames[3] = mlx_xpm_file_to_image(mlx, ENEM4, &size.x, &size.y);
	img->enemy.frames[4] = mlx_xpm_file_to_image(mlx, ENEM5, &size.x, &size.y);
	while (i < 5)
	{
		if (img->enemy.frames[i] == NULL)
			perror_free_and_exit("mlx_xpm_file_to_image() failed", game);
		i++;
	}
}
