/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:21:28 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:33:19 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_signx(float f)
{
	if (f < 0)
		return (1);
	else
		return (0);
}

static int	ft_signy(float f)
{
	if (f < 0)
		return (-1);
	else
		return (1);
}

void	ft_move(t_data *game, int direction)
{
	float	dist;
	float	dx;
	float	dy;
	float	angle;

	angle = game->look + direction * M_PI / 2;
	dx = STEP_UP * cos(angle);
	dy = STEP_UP * sin(angle);
	dist = ft_ray(game, ft_signy(dy) * M_PI / 2);
	if (dist * dist < dy * dy + 0.1)
		dy = 0.0f;
	dist = ft_ray(game, ft_signx(dx) * M_PI);
	if (dist * dist < dx * dx + 0.1)
		dx = 0.0f;
	dist = ft_ray(game, angle);
	game->x += dx;
	game->y += dy;
}

int	do_move(int key, t_data *game)
{
	if (key == KEYEXIT)
		close_game(game);
	if (key == KEYUP || key == KEYW)
		ft_move(game, 0);
	else if (key == KEYDOWN || key == KEYS)
		ft_move(game, 2);
	else if (key == KEYLEFT)
		game->look -= STEP_TURN;
	else if (key == KEYRIGHT)
		game->look += STEP_TURN;
	else if (key == KEYA)
		ft_move(game, 3);
	else if (key == KEYD)
		ft_move(game, 1);
	else if (key == KEYM)
		game->mm_show = 1 - game->mm_show;
	else
		return (1);
	ft_redraw(game);
	return (1);
}
