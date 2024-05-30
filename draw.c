/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:08 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/05/30 14:56:50 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_get_color(char *charcolor)
{
	unsigned int	color;

	color = 0;
	while (*charcolor)
	{
		charcolor++;
	}
	return (color);
}

void	draw_up_down(t_img image, t_data *game)
{
	(void)game;

	unsigned int	*img;
	int	i;

	i = 0;
	img = (unsigned int *)image.addr;
	while (i < WIN_HEIGHT * WIN_WIDTH / 2)
		img[i++] = 0x00FF0000;
	i = WIN_HEIGHT * WIN_WIDTH / 2 + 1;
	while (i < WIN_HEIGHT * WIN_WIDTH)
		img[i++] = 0x0000FF00;
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