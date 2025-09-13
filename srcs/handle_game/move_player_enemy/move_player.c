/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:59:11 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:28:11 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_player_move_valid(t_game *game, t_point new_pos)
{
	if (new_pos.x < 0 || new_pos.x >= game->map.size.x
		|| new_pos.y < 0 || new_pos.y >= game->map.size.y
		|| game->map.matrix[new_pos.y][new_pos.x] == WALL
		|| game->map.matrix[new_pos.y][new_pos.x] == ENEMY)
		return (false);
	return (true);
}

static void	check_collected_coin(t_game *game, t_point new_pos)
{
	char	new_cell;

	new_cell = game->map.matrix[new_pos.y][new_pos.x];
	if (new_cell == COIN)
		game->map.coin_count--;
}

static void	count_player_move(t_game *game)
{
	if (game->map.coin_count == 0)
		game->player.move_to_exit++;
	game->player.move_count++;
}

void	move_player(t_game *game, t_point move)
{
	t_point	new_pos;

	new_pos.x = game->player.pos.x + move.x;
	new_pos.y = game->player.pos.y + move.y;
	if (is_player_move_valid(game, new_pos) == false)
		return ;
	check_collected_coin(game, new_pos);
	game->map.matrix[game->player.pos.y][game->player.pos.x] = FREE;
	game->map.matrix[new_pos.y][new_pos.x] = PLAYER;
	game->player.pos = new_pos;
	count_player_move(game);
	if (game->map.coin_count == 0 && game->exit.moves_to_reach == 0)
		a_star_search(game, &game->astar, game->player.pos, game->exit.pos);
	if (is_player_hit(game, new_pos, ENEMY) == true)
		return ;
}
