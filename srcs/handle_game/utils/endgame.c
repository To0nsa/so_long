/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endgame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:55:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/28 12:25:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	write_loose(t_game *game)
{
	char	*loose_mes;
	char	*help_mes;
	char	*hit_mes;
	char	*sad_face;

	loose_mes = RED_C "You lost!" RESET;
	sad_face = YELLOW_C "(´סּ︵סּ`)з" RESET;
	help_mes = "To win, find the shortest way from the last tree to the exit!";
	hit_mes = "Avoid the guardians if you want to burn the whole world!";
	if (game->player.move_to_exit > game->exit.moves_to_reach
		&& game->player.hit == 0)
	{
		if (ft_printf("%s %20s\n", loose_mes, sad_face) == -1)
			perror_free_and_exit("Error\nFt_printf failed in endgame\n", game);
		if (ft_printf("%s\n", help_mes) == -1)
			perror_free_and_exit("Error\nFt_printf failed in endgame\n", game);
	}
	else if (game->player.hit != 0)
	{
		if (ft_printf("%s %20s\n", loose_mes, sad_face) == -1)
			perror_free_and_exit("Error\nFt_printf failed in endgame\n", game);
		if (ft_printf("%s\n", hit_mes) == -1)
			perror_free_and_exit("Error\nFt_printf failed in endgame\n", game);
	}
}

static void	write_win(t_game *game)
{
	char	*win_mes;

	win_mes = GREEN_C "You won! Congratulations!" RESET;
	if (ft_printf("%s\n", win_mes) == -1)
		perror_free_and_exit("Error\nFt_printf failed in wirte_win\n", game);
}

static void	endgame(t_game *game)
{
	if (game->player.move_to_exit == game->exit.moves_to_reach
		&& game->player.hit == 0)
		write_win(game);
	else
		write_loose(game);
	close_game(game);
}

static int	is_it_a_win(t_game *game)
{
	if (game->player.pos.y == game->exit.pos.y
		&& game->player.pos.x == game->exit.pos.x
		&& game->map.coin_count == 0
		&& game->player.hit == 0)
	{
		if (game->exit.reached == 0)
		{
			game->exit.reached = 1;
			game->exit.timer = (clock() * 1000) / CLOCKS_PER_SEC;
		}
		return (1);
	}
	return (0);
}

void	check_end_conditions(t_game *game)
{
	clock_t	current_time;

	current_time = (clock() * 1000) / CLOCKS_PER_SEC;
	if (game->player.hit
		&& current_time - game->player.hit_timer >= HIT_ANIMATION_DELAY)
		endgame(game);
	if (is_it_a_win(game) == true
		&& current_time - game->exit.timer >= END_DELAY)
		endgame(game);
}
