/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:16:50 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:27:23 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*error_msg(char *error)
{
	ft_printf(error);
	exit(EXIT_FAILURE);
}

void	ft_check_posibilities(t_game *game)
{
	int	x_pos;
	int	y_pos;

	x_pos = game->player->x;
	y_pos = game->player->y;
	if (game->map[y_pos][x_pos - 1] == '1' && game->map[y_pos][x_pos + 1] == '1'
		&& game->map[y_pos - 1][x_pos] == '1')
		if (game->map[y_pos + 1][x_pos] == 'E'
			&& game->map[y_pos + 2][x_pos] == 'C')
			error_msg("Wrong map format!");
	if (game->map[y_pos][x_pos - 1] == '1' && game->map[y_pos][x_pos + 1] == '1'
		&& game->map[y_pos - 1][x_pos] == '1')
		if (game->map[y_pos - 1][x_pos] == 'E'
			&& game->map[y_pos - 2][x_pos] == 'C')
			error_msg("Wrong map format!");
	if (game->map[y_pos - 1][x_pos] == '1' && game->map[y_pos + 1][x_pos] == '1'
		&& game->map[y_pos][x_pos + 1] == '1')
		if (game->map[y_pos][x_pos - 1] == 'E'
			&& game->map[y_pos][x_pos - 2] == 'C')
			error_msg("Wrong map format!");
	if (game->map[y_pos - 1][x_pos] == '1' && game->map[y_pos + 1][x_pos] == '1'
		&& game->map[y_pos][x_pos - 1] == '1')
		if (game->map[y_pos][x_pos + 1] == 'E'
			&& game->map[y_pos][x_pos + 2] == 'C')
			error_msg("Wrong map format!");
}

/**
 * @brief initialize the game.
 *
 * @param argv
 * @return char*
 */
t_game	*ft_game_init(char	*argv)
{
	t_game		*game;
	t_player	*player;
	int			fd;

	fd = open(argv, O_RDONLY);
	game = (t_game *)malloc(sizeof(t_game));
	ft_read_map(game, fd);
	close(fd);
	player = (t_player *)malloc(sizeof(t_player));
	player->x = 0;
	player->y = 0;
	player->items = 0;
	game->moves = 0;
	game->player = player;
	game->mlx = NULL;
	game->textures = (t_texture *)malloc(sizeof(t_texture));
	return (game);
}

void	ft_load_textures(t_game *game)
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*item;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;

	wall = mlx_load_png("textures/wall64px.png");
	floor = mlx_load_png("textures/floor64px.png");
	item = mlx_load_png("textures/item64px.png");
	player = mlx_load_png("textures/py64px.png");
	exit = mlx_load_png("textures/exit64px.png");
	if (!wall || !floor || !item || !player || !exit)
		error_msg("Error loading PNG's");
	game->textures->wall = mlx_texture_to_image(game->mlx, wall);
	game->textures->floor = mlx_texture_to_image(game->mlx,floor);
	game->textures->collect_item = mlx_texture_to_image(game->mlx, item);
	game->textures->player  = mlx_texture_to_image(game->mlx, player);
	game->textures->exit  = mlx_texture_to_image(game->mlx, exit);
	mlx_delete_texture(wall);
	mlx_delete_texture(floor);
	mlx_delete_texture(item);
	mlx_delete_texture(player);
	mlx_delete_texture(exit);
}

void	ft_get_item(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < game->items)
	{
		if (game->textures->collect_item->instances[i].y
			== y * 64
			&& game->textures->collect_item->instances[i].x
			== x * 64)
		{
			ft_printf("nice catch!");
			game->textures->collect_item->instances[i].enabled = false;
		}
	}
}
