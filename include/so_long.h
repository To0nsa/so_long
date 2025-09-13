/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:37:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 12:30:54 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file so_long.h
 * @author nlouis
 * @brief Main header for the so_long project.
 * @date 2024-11-19
 * 
 * This header contains all structures, macros, and function prototypes 
 * required for the main execution of the so_long game.
 */
#ifndef SO_LONG_H
# define SO_LONG_H

/** @defgroup macros
 * @brief includes External and Internal Includes
 */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdint.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"
# include "assets_paths.h"

/**
* @brief ANSI escape codes for colored terminal output.
*/
# define GREEN_C	"\033[0;32m"	/**< Green */
# define RED_C		"\033[0;31m"	/**< Red */
# define YELLOW_C	"\033[1;33m"	/**< Yellow */
# define BLUE_C		"\033[0;34m"	/**< Blue */
# define MAGENTA_C	"\033[0;35m"	/**< Magenta */
# define RESET		"\033[0m"		/**< Reset color */


/**
 * @brief Constants used for indicating success or error in functions.
 */
# define ERROR		-1	/**< Unexpected error */
# define SUCCESS	0	/**< Operation succeeded */
# define FAILURE	1	/**< Operation failed */


/**
 * @brief Character representation of game elements in the map matrix.
 */
# define FREE   '0' /**< Walkable tile */
# define WALL   '1' /**< Wall (non-walkable) */
# define COIN   'C' /**< Collectible coin */
# define PLAYER 'P' /**< Player starting position */
# define ENEMY  'N' /**< Enemy */
# define EXIT   'E' /**< Exit point */


/**
 * @brief Constants for image dimensions
 */
# define IMG_WIDTH		50	/**< Image width in pixels of the textures */
# define IMG_HEIGHT		50	/**< Image height in pixels of the textures */

/**
 * @brief Constants for window dimensions and name.
 */
# define WINDOW_WIDTH		1600		/**< Image width in pixels */
# define WINDOW_HEIGHT		1200 		/**< Image height in pixels */
# define WINDOW_NAME		"so_long"	/**< Window name */

/**
 * @brief Event codes for keyboard and window events.
 */
# define KEYPRESS			2	
# define KEYRELEASE			3
# define FOCUS_IN			9
# define FOCUS_OUT			10
# define MINIMIZED			12
# define DESTROY_NOTIFY		17
# define CONFIGURE_NOTIFY	22

/**
 * @brief Masks for event handling.
 */
# define KEYPRESS_MASK			1
# define KEYRELEASE_MASK		2
# define FOCUS_CHANGE_MASK		2097152
# define STRUCTURE_NOTIFY_MASK	131072

/**
 * @brief Keycodes for player keyboard input. (Linux)
 */
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define PAUSE	32
# define ESC	65307

/**
 * @brief Constants for enemy AI behavior.
 */
# define CHASING_RANGE			5		/**< Distance in tile from which enemy starts chasing player */
# define PATROL_RANGE			5		/**< Distance in tile to randomly select patrol points */
# define MOVE_DELAY_MS			120		/**< Delay between enemy moves in milliseconds */

/**
 * @brief Constants for game settings.
 */
# define HIT_ANIMATION_DELAY	1000	/**< Duration for player hit animation in milliseconds */
# define END_DELAY				110		/**< Delay before showing end screen in milliseconds (less than enemy move) */


/**
 * 
 */
typedef struct s_map
{
	int			fd;
	char		*filename;
	char		*line;
	char		*file;
	char		**matrix;
	char		**temp_matrix;
	t_point		size;
	t_point		flood_starting_pos;
	int			player_count;
	int			enemy_count;
	int			coin_count;
	int			exit_count;
	int			unreachable_coin;
	int			unreachable_exit;
}	t_map;

typedef struct s_window
{
	void	*ptr;
	char	*name;
	t_point	size;
	t_point	start;
	t_point	end;
}	t_window;

typedef struct s_sprite
{
	void		**frames;
	int			frame;
	int			frame_count;
	clock_t		frame_delay;
	clock_t		last_update;
}	t_sprite;

typedef struct s_img
{
	t_point		size;
	void		*coin;
	void		*free;
	void		*wall;
	t_sprite	exit;
	t_sprite	player;
	t_sprite	player_hit;
	t_sprite	enemy;
}	t_img;

typedef struct s_node
{
	t_point			pos;
	int				g_cost;
	int				h_cost;
	int				f_cost;
	struct s_node	*parent;
	struct s_node	*next;
}	t_node;

typedef struct s_closed_list
{
	t_node	**nodes;
	int		capacity;
	int		size;
}	t_closed_list;

typedef struct s_astar
{
	t_point				goal;
	t_closed_list		*closed_list;
	int					**open_list;
	t_node				*node;
	t_node				*current_node;
}	t_astar;

typedef struct s_enemy
{
	t_point	pos;
	t_point	target;
	t_point	patrol_pts[4];
	int		patrol_pts_count;
	int		patrol_point;
	int		chasing_player;
	clock_t	last_move_time;
}	t_enemy;

typedef struct s_player
{
	t_point		pos;
	int			move_count;
	int			move_to_exit;
	int			hit;
	clock_t		hit_timer;
}	t_player;

typedef struct s_exit
{
	t_point		pos;
	int			moves_to_reach;
	int			reached;
	clock_t		timer;
}	t_exit;

typedef struct s_game
{
	t_map		map;
	void		*mlx;
	t_window	window;
	t_img		img;
	t_astar		astar;
	t_point		direction[4];
	t_point		vp_size;
	t_point		vp_pos;
	t_point		drawing_pos;
	int			is_paused;
	t_enemy		*enemy;
	t_player	player;
	t_exit		exit;
}	t_game;

void	initialize_structs(t_game *game, char **argv);
void	initialize_game_struct(t_game *game, char **argv);
void	initialize_img_struct(t_img *img);
void	initialize_mlx(t_game *game);
void	initialize_enemies_patrol_pts(t_enemy *enemy, t_game *game);
void	initialize_enemies(t_game *game);

void	free_img(t_game *game);
void	free_all(t_game *game);

void	map_error(t_game *game, char *error_message, t_map *map);
void	perror_free_and_exit(char *error_message, t_game *game);

int		close_game(t_game *game);
void	fail_close_game(t_game *game);

void	check_file_type(t_game *game, t_map *map);
void	open_map(t_game *game, t_map *map);
void	read_map(t_game *game, t_map *map);
void	close_map(t_game *game, t_map *map);
void	create_map_matrix(t_game *game, t_map *map);
void	check_walls(t_game *game, t_map *map);
void	check_shape(t_game *game, t_map *map);
void	count_elements(t_game *game, t_map *map);
void	check_elements(t_game *game, t_map *map);
void	validate_map_paths(t_game *game, t_map *map);
void	generate_map(t_game *game, t_map *map);

void	load_collectible_images(t_img *img, void *mlx, t_game *game);
void	load_exit_images(t_img *img, void *mlx, t_game *game);
void	load_free_space_images(t_img *img, void *mlx, t_game *game);
void	load_player_images(t_img *img, void *mlx, t_game *game);
void	load_wall_images(t_img *img, void *mlx, t_game *game);
void	load_enemy_images(t_img *img, void *mlx, t_game *game);
void	load_images(t_game *game);

void	update_vp(t_game *game, t_window *window);
void	define_vp_boundaries(t_game *game, t_window *window, t_map *map);
int		is_within_vp(t_point pos, t_point wind_start, t_point win_end);

void	update_animation(t_img *img);
t_point	calculate_drawing_pos(t_game *game, t_point element_pos,
			t_point vp_pos);

void	draw_free_spaces(t_game *game, t_map *map, t_img *img);
void	draw_walls(t_game *game, t_map *map, t_img *img);
void	draw_collectibles(t_game *game, t_map *map, t_img *img);
void	draw_exit(t_game *game, t_map *map, t_img *img);
void	draw_player(t_game *game, t_img *img);
void	draw_player_hit(t_game *game, t_img *img);
void	draw_enemy(t_game *game, t_map *map, t_img *img);
void	write_moves(t_game *game);
void	draw_game(t_game *game);

int		game_loop(t_game *game);
void	handle_event_hooks(t_game *game, t_window *window);
void	check_end_conditions(t_game *game);

void	move_player(t_game *game, t_point move);
void	move_enemies(t_game *game);

void	scan_exit_pos(t_game *game, t_map *map);
void	scan_player_pos(t_game *game, t_map *map);
void	scan_enemies_pos(t_game *game, t_map *map);
void	scan_positions(t_game *game);
bool	is_player_hit(t_game *game, t_point new_pos, char target);

void	swap_nodes(t_node **a, t_node **b);
void	closed_list_insert(t_closed_list *closed_list, t_node *node,
			t_game *game);
t_node	*closed_list_extract_min(t_closed_list *closed_list);
void	reconstruct_path(t_game *game, t_node *goal_node);
void	setup_astar_struct(t_game *game, t_astar *astar, t_point start,
			t_point goal);
void	spread_child_node(t_game *game, t_astar *astar);
void	reset_astar_struct(t_astar *astar, t_game *game);
void	a_star_search(t_game *game, t_astar *astar, t_point start,
			t_point goal);
t_node	*a_star_for_enemy(t_game *game, t_astar *astar, t_point start,
			t_point goal);
#endif