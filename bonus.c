/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:24:43 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:31:52 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img_mm(t_data *game)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(game->mlx, "img/mm_player.xpm",
			&img.width, &img.height);
	img.addr = (unsigned int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.size_line, &img.endian);
	game->mm_player = img;
	img.img = mlx_xpm_file_to_image(game->mlx, "img/mm_wall.xpm",
			&img.width, &img.height);
	img.addr = (unsigned int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.size_line, &img.endian);
	game->mm_wall = img;
}

void	print_mm(t_data *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_game_height)
	{
		x = -1;
		while (game->map_game[y][++x])
		{
			if (game->map_game[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->mm_wall.img, x * MM_SIZE, y * MM_SIZE);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->mm_player.img, (int)game->x * MM_SIZE,
		(int)game->y * MM_SIZE);
}
