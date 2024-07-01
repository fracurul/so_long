/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:16:59 by fracurul          #+#    #+#             */
/*   Updated: 2024/07/01 17:27:32 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error_msg("Invalid parameters");
	game = ft_game_init(argv[1]);
	ft_check_map(game);
	game->mlx = mlx_init(game->n_rows * 64, game->n_col * 64, "so_long", false);
	ft_load_textures(game);
	if (!game->mlx)
		error_msg("MLX42 error");
	ft_render_map(game);
	ft_render_player(game);
	mlx_key_hook(game->mlx, &ft_moves, game);
	mlx_loop(game->mlx);
	return (0);
}
