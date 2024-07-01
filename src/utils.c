/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:38 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:48:43 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_game(t_game *game)
{
	mlx_delete_image(game->mlx, game->textures->wall);
	mlx_delete_image(game->mlx, game->textures->floor);
	mlx_delete_image(game->mlx, game->textures->collect_item);
	mlx_delete_image(game->mlx, game->textures->player);
	mlx_delete_image(game->mlx, game->textures->exit);
	ft_free_map(game->map);
}

int	ft_win(t_game *game, int x, int y)
{
	char **map;
	int		item_cnt;
	map = game->map;
	item_cnt = game->player->items;
	if (map[y][x] == 'E' && item_cnt == game->items)
		return (ft_free_game(game), mlx_close_window(game->mlx), 1);
	return (0);
}

void	print_map(char** map)
{
	int	i = 0;
	int j = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("%c", map[i][j]);
			j++;
		}
		write (1, "\n", 1);
		i++;
	}
}

void	no_exit(char **map)
{
	int y;
	int x;

	y = -1;
	while(map[++y])
	{
		x =-1;
		while(map[y][++x])
		{
			if (map[y][x] == 'E')
			{
				if (map[y - 1][x] != 'F' && map[y + 1][x] != 'F'
					&& map[y][x - 1] != 'F' && map[y][x + 1] != 'F')
						error_msg("there is no path to exit");
			}
		}
	}
}
