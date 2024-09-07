/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:32:17 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	save_map_game(t_data *data, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	data->map_game_width_max = 0;
	data->map_game = (char **)malloc(sizeof(char *)
			* (data->map_height - i + 1));
	while (i < data->map_height)
	{
		data->map_game[j] = ft_strdup(data->map[i]);
		if (data->map_game_width_max < (int)ft_strlen(data->map_game[j]))
			data->map_game_width_max = ft_strlen(data->map_game[j]);
		i++;
		j++;
		data->map_game_height++;
	}
	data->map_game[j] = NULL;
}

void	parse_elements(t_data *data)
{
	int	i;
	int	j;
	int	elements;

	i = 0;
	j = 0;
	elements = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j] == ' ')
			j++;
		if (((data->map[i][j] == 'N' && data->map[i][j + 1] == 'O')
				|| (data->map[i][j] == 'S' && data->map[i][j + 1] == 'O')
				|| (data->map[i][j] == 'W' && data->map[i][j + 1] == 'E')
				|| (data->map[i][j] == 'E' && data->map[i][j + 1] == 'A'))
			&& data->map[i][j + 2] == ' ' && elements < 6)
		{
			save_img_path(data, data->map[i], data->map[i][j], j + 2);
			elements++;
		}
		else if ((data->map[i][j] == 'F' || data->map[i][j] == 'C')
			&& data->map[i][j + 1] == ' ' && elements < 6)
		{
			save_colors(data, data->map[i], data->map[i][j], j + 1);
			elements++;
		}
		else if (data->map[i][j] == '\n')
		{
			i++;
			continue ;
		}
		else if (elements == 6 && data->map[i][j] == '1')
			break ;
		else
			error(data, "The map is not valid.");
		i++;
	}
	check_imgs(data);
	save_map_game(data, i);
}

void	parse_map(t_data *data)
{
	parse_elements(data);
	check_map_chars(data);
	check_walls0(data);
	check_walls(data);
}
