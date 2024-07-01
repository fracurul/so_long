/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:13 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:27:00 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_set_player_pos(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				game->player->x = x;
				game->player->y = y;
			}
			x++;
		}
		y++;
	}
}

int	ft_map_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);

}

void	ft_free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

char	**ft_cpymap(char **map, int size_x)
{
	char **copy;
	int		y;
	int		x;

	copy = (char **)malloc((ft_map_height(map) + 1) * sizeof(char *));
	if (!copy)
		return (ft_free_map(copy), NULL);
	y = -1;
	while (map[++y])
	{
		x = -1;
		copy[y] = (char *)malloc(size_x * sizeof(char));
		if(!copy[y])
			return(free(copy[y]), NULL);
		while (map[y][++x])
		{
			copy[y][x] = map[y][x];
		}
		copy[y][x] = '\0';
	}
	copy[y] = '\0';
	return (copy);
}

void	ft_fill_map(char **map, int x, int y)
{
	if (x < 0 || y < 0 || map[y][x] == '1' || map[y][x] == 'F'
		|| map[y][x] == 'E')
			return ;
	if (map[y][x] == 'C')
		map[y][x] = '0';
	map[y][x] = 'F';
	ft_fill_map(map, x + 1, y);
	ft_fill_map(map, x - 1, y);
	ft_fill_map(map, x, y + 1);
	ft_fill_map(map, x, y - 1);
}
