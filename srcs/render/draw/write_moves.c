/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:09:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:10:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	write_moves(t_game *game)
{
	t_point	pos;
	char	*str;
	char	*n_move;
	char	*new_str;

	pos.x = 70;
	pos.y = 70;
	str = "MOVES: ";
	n_move = ft_itoa(game->player.move_count);
	new_str = ft_strjoin(str, n_move);
	mlx_string_put(game->mlx, game->window.ptr, pos.x, pos.y,
		0xFFFFFF, new_str);
	free(n_move);
	free(new_str);
}
