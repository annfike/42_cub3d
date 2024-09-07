/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:19:11 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/09/07 16:30:05 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ft_ray(t_data *game, float look)
{
	float	c;
	float	maxray;
	float	x;
	float	y;
	float	dif_x;
	float	dif_y;

	maxray = sqrt(pow(game->map_game_height, 2)
			+ pow(game->map_game_width_max, 2));
	c = 0;
	while (c < maxray)
	{
		x = game->x + c * cos(look);
		y = game->y + c * sin(look);
		if (game->map_game[(int)floor(y)][(int)floor(x)] == '1')
		{
			dif_x = x - (int)x;
			dif_y = y - (int)y;
			game->txt_w = 0;
			if (dif_x <= 0.01)
			{
				game->txt_idx = 2;
				game->txt_w = dif_y;
			}
			else if (dif_y <= 0.01)
			{
				game->txt_idx = 0;
				game->txt_w = dif_x;
			}
			else if (dif_x >= 0.99)
			{
				game->txt_idx = 3;
				game->txt_w = 1 - dif_y;
			}
			else if (dif_y >= 0.99)
			{
				game->txt_idx = 1;
				game->txt_w = 1 - dif_x;
			}
			break ;
		}
		c += 0.01;
	}
	return (c);
}

void	draw_line(t_data *game, int x, float dist, t_img img)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	wall_h;
	float			txt_h;
	float			step;
	t_img			img_txt;

	wall_h = WIN_HEIGHT / dist;
	txt_h = 0.0f;
	img_txt = game->images[game->txt_idx];
	step = (float)img_txt.height / wall_h;
	if (wall_h > WIN_HEIGHT)
	{
		txt_h = 0.5f * (wall_h - WIN_HEIGHT) / wall_h * img_txt.height;
		wall_h = WIN_HEIGHT;
	}
	src = img_txt.addr;
	src += (int)((float)game->txt_w * img_txt.width);
	dst = img.addr + x + (WIN_HEIGHT - wall_h) / 2 * WIN_WIDTH;
	while (wall_h-- > 0)
	{
		*dst = *(src + ((int)txt_h) * img_txt.width);
		dst += WIN_WIDTH;
		txt_h += step;
	}
}
