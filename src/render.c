/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:28 by fracurul          #+#    #+#             */
/*   Updated: 2024/06/27 18:53:28 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render(t_game *game, int x, int y)
{
	mlx_image_to_window(game->mlx, game->textures->floor, x * 64, y * 64);
	if (game->map[y][x] == '1')
		mlx_image_to_window(game->mlx, game->textures->wall, x * 64, y * 64);
	if (game->map[y][x] == 'C')
	{
		mlx_image_to_window(game->mlx, game->textures->collect_item, x * 64, y * 64);
		game->items++;
	}
	if (game->map[y][x] == 'E')
		mlx_image_to_window(game->mlx, game->textures->exit, x * 64, y * 64);
}

void	ft_render_player(t_game *game)
{
	int	x;
	int	y;

	x = game->player->x;
	y = game->player->y;
	while(game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				mlx_image_to_window(game->mlx, game->textures->player, x * 64, y * 64);
				game->player->x = x;
				game->player->y = y;
			}
			x++;
		}
		y++;
	}
}

void	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			ft_render(game, x, y);
			x++;
		}
		y++;
	}
}
