/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:19:11 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/09/09 12:04:03 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_img(t_data *game, float x, float y)
{
	game->txt_w = 0;
	if (x - (int)x <= 0.01)
	{
		game->txt_idx = 2;
		game->txt_w = y - (int)y;
	}
	else if (y - (int)y <= 0.01)
	{
		game->txt_idx = 0;
		game->txt_w = x - (int)x;
	}
	else if (x - (int)x >= 0.99)
	{
		game->txt_idx = 3;
		game->txt_w = 1 - (y - (int)y);
	}
	else if (y - (int)y >= 0.99)
	{
		game->txt_idx = 1;
		game->txt_w = 1 - (x - (int)x);
	}
}

float	ft_ray(t_data *game, float look)
{
	float	c;
	float	maxray;
	float	x;
	float	y;

	maxray = sqrt(pow(game->map_game_height, 2)
			+ pow(game->map_game_width_max, 2));
	c = 0;
	while (c < maxray)
	{
		x = game->x + c * cos(look);
		y = game->y + c * sin(look);
		if (game->map_game[(int)floor(y)][(int)floor(x)] == '1')
		{
			set_img(game, x, y);
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

	wall_h = WIN_HEIGHT / dist;
	txt_h = 0.0f;
	step = (float)game->images[game->txt_idx].height / wall_h;
	if (wall_h > WIN_HEIGHT)
	{
		txt_h = 0.5f * (wall_h - WIN_HEIGHT) / wall_h
			* game->images[game->txt_idx].height;
		wall_h = WIN_HEIGHT;
	}
	src = game->images[game->txt_idx].addr;
	src += (int)((float)game->txt_w * game->images[game->txt_idx].width);
	dst = img.addr + x + (WIN_HEIGHT - wall_h) / 2 * WIN_WIDTH;
	while (wall_h-- > 0)
	{
		*dst = *(src + ((int)txt_h) * game->images[game->txt_idx].width);
		dst += WIN_WIDTH;
		txt_h += step;
	}
}
