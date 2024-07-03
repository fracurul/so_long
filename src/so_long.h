/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:34 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/03 15:49:11 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/get_next_line_bonus.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct t_player
{
	int	x;
	int	y;
	int	items;

}				t_player;

typedef struct t_texture
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	mlx_image_t	*collect_item;
}				t_texture;

typedef struct t_game
{
	char		**map;
	mlx_t		*mlx;
	t_player	*player;
	t_texture	*textures;
	int			n_rows;
	int			n_col;
	int			moves;
	int			items;
}				t_game;

void	print_map(char** map);
// Map //
int		ft_read_map(t_game *game, int fd);
void	ft_check_walls(char **game, int size_x, int size_y);
void	ft_check_path(char **map);
void	ft_check_instance(char **map);
//bool	ft_check_path(t_game *game, char **map, int x, int y);
void	ft_check_map(t_game *game);
// Player moves //
void	ft_up(t_game *game);
void	ft_down(t_game *game);
void	ft_right(t_game *game);
void	ft_left(t_game *game);
// Render //
void	ft_render(t_game *game, int x, int y);
void	ft_render_player(t_game *game);
void	ft_render_map(t_game *game);
void	ft_moves(mlx_key_data_t keydata, void *param);
// Utils //
//-> Utils
void	ft_free_game(t_game *game);
int		ft_win(t_game *game, int x, int y);
void	no_exit(char **map);
//-> Game utils
char	*error_msg(char *error);
void	ft_check_posibilities(t_game *game);
t_game	*ft_game_init(char	*argv);
void	ft_load_textures(t_game *game);
void	ft_get_item(t_game *game, int x, int y);
///-> Map utils //
void	ft_set_player_pos(t_game *game, char **map);
int		ft_map_height(char **map);
void	ft_free_map(char **map);
char	**ft_cpymap(char	**map, int size_x);
void	ft_fill_map(char **map, int x_pos, int y_pos);
#endif
