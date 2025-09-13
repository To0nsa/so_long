/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:25:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:03:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_astar_nodes(t_astar *astar)
{
	t_node	*current;
	t_node	*temp;

	current = astar->node;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	astar->node = NULL;
}

static void	free_priority_queue(t_closed_list *closed_list)
{
	if (!closed_list)
		return ;
	if (closed_list->nodes)
	{
		free(closed_list->nodes);
		closed_list->nodes = NULL;
	}
	closed_list->size = 0;
	closed_list->capacity = 0;
}

void	reset_astar_struct(t_astar *astar, t_game *game)
{
	free_astar_nodes(astar);
	if (astar->closed_list)
	{
		free_priority_queue(astar->closed_list);
		free(astar->closed_list);
		astar->closed_list = NULL;
	}
	if (astar->open_list)
	{
		ft_free_array_size((void **)astar->open_list, game->map.size.y);
		astar->open_list = NULL;
	}
}

static void	cleanup_sprite(t_sprite *sprite, void *mlx, int frame_count)
{
	int	i;

	i = 0;
	if (sprite->frames != NULL)
	{
		while (i < frame_count)
		{
			if (sprite->frames[i])
				mlx_destroy_image(mlx, sprite->frames[i]);
			i++;
		}
		free(sprite->frames);
		sprite->frames = NULL;
	}
}

void	free_img(t_game *game)
{
	if (game->img.coin)
		mlx_destroy_image(game->mlx, game->img.coin);
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.free)
		mlx_destroy_image(game->mlx, game->img.free);
	if (game->img.exit.frames)
		cleanup_sprite(&game->img.exit, game->mlx, 8);
	if (game->img.player.frames)
		cleanup_sprite(&game->img.player, game->mlx, 5);
	if (game->img.player_hit.frames)
		cleanup_sprite(&game->img.player_hit, game->mlx, 3);
	if (game->img.enemy.frames)
		cleanup_sprite(&game->img.enemy, game->mlx, 5);
}

void	free_all(t_game *game)
{
	free_img(game);
	if (game->window.ptr)
	{
		mlx_clear_window(game->mlx, game->window.ptr);
		mlx_destroy_window(game->mlx, game->window.ptr);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	reset_astar_struct(&game->astar, game);
	if (game->map.line)
		free(game->map.line);
	if (game->map.matrix)
		ft_free_array_size((void **)game->map.matrix, game->map.size.y);
	if (game->enemy)
		free(game->enemy);
}
