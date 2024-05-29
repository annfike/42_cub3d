/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:08 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/05/29 19:00:55 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_up_down(void *img, t_data *game)
{
	(void)game;
	(void)img;
}

void	ft_reload(t_data *game)
{
	void	*img;
	
	img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_up_down(img, game);
	//
	mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
	mlx_destroy_image(game->mlx, img);
}