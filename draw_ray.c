/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:19:11 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/06/09 14:51:38 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_data *game, int x, float dist, t_img img)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	h;
	float			src_f;
	float			d_shift;

	h = WIN_HEIGHT / dist;
	src_f = 0.0f;
	d_shift = (float) game->images[game->txt_idx].height / h;
	if (h > WIN_HEIGHT)
	{
		src_f = 0.5f * (h - WIN_HEIGHT) / h * game->images[game->txt_idx].height;
		h = WIN_HEIGHT;
	}
	src = game->images[game->txt_idx].addr;
	src += (int)((float) game->txt_w * game->images[game->txt_idx].width);
	dst = img.addr + x + (WIN_HEIGHT - h) / 2 * WIN_WIDTH;
	while (h-- > 0)
	{
		*dst = *(src + ((int)src_f) * game->images[game->txt_idx].width);
		//*dst = game->txt_idx * 255 + (1 - game->txt_idx) * (255 << 8);
		//*dst = 0xFFFF00;
		dst += WIN_WIDTH;
		src_f += d_shift;
	}
}

int	ft_sign(float f)
{
	if (f < 0.0f)
	{
		if (f > -0.001)
			return (0);
		else
			return (-1);
	}
	else
	{
		if (f < 0.001f)
			return (0);
		else
			return (1);
	}
}

static void	ft_ray_initial_calculations(t_data *game, t_ray *r, float look)
{
	r->dx = cos(look);
	r->dy = -sin(look);
	r->sx = ft_sign(r->dx);
	r->sy = ft_sign(r->dy);
	r->vert_x = (int) game->x;
	if (r->sx > 0)
		r->vert_x += 1.0f;
	r->hor_y = (int) game->y;
	if (r->sy > 0)
		r->hor_y += 1.0f;
}

static void	ft_ray_next_step_calculation(t_data *game, t_ray *r)
{
	if (r->sx != 0)
	{
		r->vert_y = game->y + r->dy / r->dx * (r->vert_x - game->x);
		r->vert_dist = sqrt(pow(game->x - r->vert_x, 2.0)
				+ pow(game->y - r->vert_y, 2.0));
		r->vert_w = r->vert_y - (int) r->vert_y;
		if (r->sx > 0)
			r->vert_w = 1 - r->vert_w;
	}
	else
		r->vert_dist = INFINITY;
	if (r->sy != 0)
	{
		r->hor_x = game->x + r->dx / r->dy * (r->hor_y - game->y);
		r->hor_dist = sqrt(pow(game->x - r->hor_x, 2.0)
				+ pow(game->y - r->hor_y, 2.0));
		r->hor_w = r->hor_x - (int) r->hor_x;
		if (r->sy < 0)
			r->hor_w = 1 - r->hor_w;
	}
	else
		r->hor_dist = INFINITY;
}

float	ft_ray(t_data *game, float look)
{
	t_ray	r;

	ft_ray_initial_calculations(game, &r, look);
	while (1)
	{
		ft_ray_next_step_calculation(game, &r);
		if (r.vert_dist < r.hor_dist)
		{
			if (game->map_game[(int)r.vert_y][(int)r.vert_x + (r.sx - 1) / 2] == '1')
			{
				game->txt_idx = r.sx + 1;
				game->txt_w = r.vert_w;
				return (r.vert_dist);
			}				
			else
				r.vert_x += r.sx;
		}
		else
		{
			if (game->map_game[(int)r.hor_y + (r.sy - 1) / 2][(int)r.hor_x] == '1')
			{
				game->txt_idx = r.sy + 2;
				game->txt_w = r.hor_w;
				return (r.hor_dist);
			}
			else
				r.hor_y += r.sy;
		}
	}
	return 1;
}