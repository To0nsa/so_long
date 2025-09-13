/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:08:53 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 11:55:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	reconstruct_path(t_game *game, t_node *goal_node)
{
	t_node	*current;

	current = goal_node;
	while (current != NULL)
	{
		game->exit.moves_to_reach++;
		current = current->parent;
	}
}
