/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:08 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/09/05 15:05:03 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_get_color(int colors[3])
{
	unsigned int	color;

	color = colors[0] << 16 | colors[1] << 8 | colors[2];
	return (color);
}

void	draw_up_down(t_img image, t_data *game)
{
	int	i;

	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH / 2)
		image.addr[i++] = ft_get_color(game->c_colors);
	while (i < WIN_HEIGHT * WIN_WIDTH)
		image.addr[i++] =  ft_get_color(game->f_colors);
}

void draw(t_img image, t_data *game)
{
	int	x;
	float	delta;
	float	look;
	
	x = 0;
	look = game->look - FOV / 2;	
	delta = FOV / (WIN_WIDTH - 1);
	while (x < WIN_WIDTH)
	{
		draw_line(game, x, ft_ray2(game, look) * cos(game->look - look), image);
		look += delta;
		x++;
	}
}

void	ft_redraw(t_data *game)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.width = WIN_WIDTH;
	img.height = WIN_HEIGHT;
	img.addr = (unsigned int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	draw_up_down(img, game);
	draw(img, game);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
