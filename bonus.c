/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:24:43 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/09 11:44:48 by adelaloy         ###   ########.fr       */
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
		game->mm_player.img, game->x * MM_SIZE - game->mm_player.width/2, 
		game->y * MM_SIZE - game->mm_player.height/2);
	
	//int x1 = game->x * MM_SIZE;
	float x1;
	float y1;
	float l = game->look - 0.5;
	while (l < game->look + 0.5)
	{
		float c = 0;
		while (c < 15)
		{		
			x1 = c * cos(l);
			y1 = c * sin(l);
			//printf("x: %f, y: %f\n", x1, y1);
			mlx_pixel_put(game->mlx, game->win, game->x * MM_SIZE + x1, game->y* MM_SIZE  + y1, 0xFF47CA);		
			c += 0.1;
		}
		l += 0.05;
	}	
}
