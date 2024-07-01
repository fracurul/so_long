/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:17:19 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:48:14 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief read the map and keep it into game->map.
 *
 * @param game struture for our game.
 * @param fd we read our map.
 */
int	ft_read_map(t_game *game, int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	tmp = NULL;
	if (!line)
		return (free(line), error_msg("Reading error"), 1);
	while (line)
	{
		tmp = gnl_strjoin(tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	line = tmp;
	while(*line)
	{
		if(*line == '\n' && (*(line + 1) == '\n'))
			return (free(tmp), error_msg("Wrong map format"), 1);
		line++;
	}
	game->map = ft_split(tmp, '\n');
	return (free(tmp), 0);
}

/**
 * @brief check for walls
 *
 * @param game the map we've
 * @param size_x
 * @param size_y
 */
void	ft_check_walls(char **map, int size_x, int size_y)
{
	int	y;
	int	x;

	y = 0;
	while(map[y])
	{
		x = 0;
		if (ft_strlen(map[y]) != (size_t)size_x)
			error_msg("Wrong map format!");
		while(map[y][x])
		{
			if (map[0][x] != '1')
				error_msg("Wrong map format!");
			if (map[size_y - 1][x] != '1')
				error_msg("Wrong map format!");
			if (map[y][0] != '1')
				error_msg("Wrong map format!");
			if (map[y][size_x - 1] != '1')
				error_msg("Wrong map format!");
			x++;
		}
		x = 0;
		y++;
	}
}

/**
 * @brief check if we've all the things to start the game.
 *
 * @param map
 */
void	ft_check_instance(char **map)
{
	int	x;
	int	y;
	int	player;
	int	item;
	int	exit;

	y = -1;
	player = 0;
	exit = 0;
	item = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'P'
			|| map[y][x] == 'C' || map[y][x] == 'E'))
		{
			if (map[y][x] == 'P')
				player++;
			if (map[y][x] == 'C')
				item++;
			if (map[y][x] == 'E')
				exit++;
		}
	}
	if (player != 1 || item < 1 || exit != 1)
		error_msg("Wrong map format");
}

/**
 * @brief check for an exit path.
 *
 * @param map
 */
void	ft_check_path(char **map)
{
	int	y;
	int	x;

	y = 0;
	if (!map)
		error_msg("No map to check a valid path");
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				error_msg("There is not a valid path to complete the game");
			x++;
		}
		y++;
	}
}
/**
 * @brief check if our map have all the parameters needed to be played.
 *
 * @param game
 */
void	ft_check_map(t_game *game)
{
	char	**map_cpy;
	int		size_x;
	int		size_y;

	size_y = ft_map_height(game->map);
	size_x = (int )ft_strlen(game->map[0]);
	game->n_col = size_y;
	game->n_rows = size_x;
	if (size_y > size_x)
		error_msg("wrong map format!");
	map_cpy = ft_cpymap(game->map, size_x);
	if(!map_cpy)
		error_msg("failure copying the map");
	ft_check_walls(map_cpy, size_x, size_y);
	ft_check_instance(map_cpy);
	ft_set_player_pos(game, map_cpy);
	ft_fill_map(map_cpy, game->player->x, game->player->y);
	ft_check_path(map_cpy);
	no_exit(map_cpy);
	ft_check_posibilities(game);
	ft_free_map(map_cpy);
}
