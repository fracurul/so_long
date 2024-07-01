/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:24 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:27:57 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_up(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = game->player->x;
	y = game->player->y;
	map = game->map;
	ft_printf("%c", map[y - 1][x]);
	if (map[y - 1][x] == '1')
		return ;
	if ((!ft_win(game, x, y - 1) && map[y - 1][x] == 'E'))
			return ;
	if (map[y - 1][x] == 'C')
	{
		ft_get_item(game, x, y - 1);
		game->player->items++;
	}
	map[y][x] = '0';
	map[y - 1][x] = 'P';
	game->player->y--;
	game->textures->player->instances[0].y -= 64;
	game->moves++;
	ft_printf("Me desplazo a y->%d, x->%d\n", game->player->y, game->player->x);
	ft_printf("moves UP; %d\n", game->moves);
}

void	ft_down(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = game->player->x;
	y = game->player->y;
	map = game->map;
	if (map[y + 1][x] == '1' || (map[y + 1][x] == 'E'
		&& !ft_win(game, x, y + 1)))
			return ;
	if (map[y + 1][x] == 'C')
	{
		ft_get_item(game, x, y + 1);
		game->player->items++;
	}
	game->map[y][x] = '0';
	game->map[y + 1][x] = 'P';
	game->player->y++;
	game->textures->player->instances[0].y += 64;
	game->moves++;
	ft_printf("moves; DOWN %d\n", game->moves);
}

void	ft_right(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = game->player->x;
	y = game->player->y;
	map = game->map;
	ft_printf("%c", map[y][x + 1]);
	if ((map[y][x + 1] == 'E' && !ft_win(game, x + 1, y)) || map[y][x + 1] == '1')
			return ;
	if (map[y][x + 1] == 'C')
	{
		ft_printf("llega");
		ft_get_item(game, x + 1, y);
		game->player->items++;
	}
	game->map[y][x] = '0';
	game->map[y][x + 1] = 'P';
	game->player->x++;
	game->textures->player->instances[0].x += 64;
	game->moves++;
	ft_printf("moves RIGHT; %d\n", game->moves);
}

void	ft_left(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = game->player->x;
	y = game->player->y;
	map = game->map;
	if (map[y][x - 1] == '1' || (map[y][x - 1] == 'E'
		&& !ft_win(game, x - 1, y)))
			return ;
	if (map[y][x - 1] == 'C')
	{
		ft_get_item(game, x -1, y);
		game->player->items++;
	}
	game->map[y][x] = '0';
	game->map[y][x - 1] = 'P';
	game->player->x--;
	game->textures->player->instances[0].x -= 64;
	game->moves++;
	ft_printf("moves LEFT; %d\n", game->moves);
}

void	ft_moves(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		ft_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		ft_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_right(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_free_game(game);
		mlx_close_window(game->mlx);
	}
}
