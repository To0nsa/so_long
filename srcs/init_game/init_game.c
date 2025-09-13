/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:04:11 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_game_struct(t_game *game, char **argv)
{
	ft_memset(game, 0, sizeof(t_game));
	game->direction[0] = (t_point){0, -1};
	game->direction[1] = (t_point){1, 0};
	game->direction[2] = (t_point){0, 1};
	game->direction[3] = (t_point){-1, 0};
	game->window.name = WINDOW_NAME;
	game->window.size = (t_point){WINDOW_WIDTH, WINDOW_HEIGHT};
	game->map.filename = argv[1];
}

static void	initialize_sprite_struct(t_sprite *sprite, clock_t frame_delay_ms,
	int frame_count)
{
	sprite->frame_delay = (frame_delay_ms * CLOCKS_PER_SEC) / 1000;
	sprite->frame_count = frame_count;
	sprite->last_update = clock();
}

void	initialize_img_struct(t_img *img)
{
	img->size = (t_point){IMG_WIDTH, IMG_HEIGHT};
	initialize_sprite_struct(&img->exit, 90, 8);
	initialize_sprite_struct(&img->player, 60, 5);
	initialize_sprite_struct(&img->player_hit, 60, 3);
	initialize_sprite_struct(&img->enemy, 60, 5);
}

void	initialize_enemies(t_game *game)
{
	if (game->map.enemy_count > 0)
	{
		game->enemy = ft_calloc(game->map.enemy_count, sizeof(t_enemy));
		if (!game->enemy)
			perror_free_and_exit("Error\nMalloc failed for enemies\n",
				game);
		initialize_enemies_patrol_pts(game->enemy, game);
	}
}

void	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		perror_free_and_exit("Error\nmlx_init() failed\n", game);
	game->window.ptr = mlx_new_window(game->mlx, game->window.size.x,
			game->window.size.y, game->window.name);
	if (!game->window.ptr)
		perror_free_and_exit("Error\nmlx_new_window() failed\n", game);
}

void	initialize_structs(t_game *game, char **argv)
{
	initialize_game_struct(game, argv);
	initialize_img_struct(&game->img);
	initialize_mlx(game);
}
