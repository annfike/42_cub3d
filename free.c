/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:40 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:21:27 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	free_map_game(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_game_height)
	{
		free(data->map_game[i]);
		i++;
	}
	free(data->map_game);
}

void	free_all(t_data *data)
{
	free_map(data);
	free_map_game(data);
	if (data->img_path[0])
		free(data->img_path[0]);
	if (data->img_path[1])
		free(data->img_path[1]);
	if (data->img_path[2])
		free(data->img_path[2]);
	if (data->img_path[3])
		free(data->img_path[3]);
	if (data->images[0].img)
		mlx_destroy_image(data->mlx, data->images[0].img);
	if (data->images[1].img)
		mlx_destroy_image(data->mlx, data->images[1].img);
	if (data->images[2].img)
		mlx_destroy_image(data->mlx, data->images[2].img);
	if (data->images[3].img)
		mlx_destroy_image(data->mlx, data->images[3].img);
}

void	error(t_data *game, char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	if (game)
		free_all(game);
	exit(0);
}

void	close_game(t_data *game)
{
	(void)game;
	exit(0);
}
