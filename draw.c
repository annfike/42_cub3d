/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:08 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/05/30 16:10:44 by dmiasnik         ###   ########.fr       */
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
	unsigned int	*img;
	int	i;

	(void)game;
	i = 0;
	img = (unsigned int *)image.addr;
	while (i < WIN_HEIGHT * WIN_WIDTH / 2)
		img[i++] = ft_get_color(game->c_colors);
	while (i < WIN_HEIGHT * WIN_WIDTH)
		img[i++] =  ft_get_color(game->f_colors);
}

void	ft_redraw(t_data *game)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	draw_up_down(img, game);

	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
