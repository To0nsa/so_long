/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:11:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:11:13 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	get_next_position_in_path(t_node *path_goal, t_point start_pos)
{
	t_node	*current;

	current = path_goal;
	while (current->parent != NULL)
	{
		if (current->parent->pos.x == start_pos.x
			&& current->parent->pos.y == start_pos.y)
			return (current->pos);
		current = current->parent;
	}
	return (path_goal->pos);
}

static void	move_enemy(t_game *game, t_enemy *enemy)
{
	t_node	*path_goal;
	t_point	new_pos;

	path_goal = a_star_for_enemy(game, &game->astar,
			enemy->pos, enemy->target);
	if (!path_goal || !path_goal->parent)
		return ;
	new_pos = get_next_position_in_path(path_goal, enemy->pos);
	if (new_pos.x < 0 || new_pos.x >= game->map.size.x
		|| new_pos.y < 0 || new_pos.y >= game->map.size.y
		|| game->map.matrix[new_pos.y][new_pos.x] == ENEMY
		|| game->map.matrix[new_pos.y][new_pos.x] == COIN
		|| game->map.matrix[new_pos.y][new_pos.x] == PLAYER
		|| game->map.matrix[new_pos.y][new_pos.x] == EXIT)
		return ;
	game->map.matrix[enemy->pos.y][enemy->pos.x] = FREE;
	game->map.matrix[new_pos.y][new_pos.x] = ENEMY;
	if (is_player_hit(game, new_pos, PLAYER) == 1)
		return ;
	enemy->pos = new_pos;
}

static void	update_enemy_target(t_game *game, t_enemy *enemy)
{
	int	manhattan_dist;

	if (enemy->chasing_player)
	{
		enemy->target = game->player.pos;
		return ;
	}
	manhattan_dist = ft_manhattan_dist_point(game->player.pos, enemy->pos);
	if (manhattan_dist <= CHASING_RANGE)
	{
		enemy->chasing_player = 1;
		enemy->target = game->player.pos;
	}
	else
	{
		enemy->chasing_player = 0;
		enemy->target = enemy->patrol_pts[enemy->patrol_point];
	}
}

static void	update_patrol_target(t_enemy *enemy)
{
	if (enemy->pos.x == enemy->target.x
		&& enemy->pos.y == enemy->target.y)
	{
		enemy->patrol_point = (enemy->patrol_point + 1)
			% enemy->patrol_pts_count;
		enemy->target = enemy->patrol_pts[enemy->patrol_point];
	}
}

void	move_enemies(t_game *game)
{
	clock_t	current_time;
	clock_t	move_delay_ticks;
	int		i;

	if (game->map.enemy_count == 0)
		return ;
	current_time = clock();
	i = 0;
	while (i < game->map.enemy_count)
	{
		move_delay_ticks = (MOVE_DELAY_MS * CLOCKS_PER_SEC) / 1000;
		if (current_time - game->enemy[i].last_move_time >= move_delay_ticks)
		{
			game->enemy[i].last_move_time = current_time;
			update_enemy_target(game, &game->enemy[i]);
			if (game->enemy[i].chasing_player)
				move_enemy(game, &game->enemy[i]);
			else
			{
				update_patrol_target(&game->enemy[i]);
				move_enemy(game, &game->enemy[i]);
			}
		}
		i++;
	}
}
