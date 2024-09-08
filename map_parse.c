/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/08 11:56:11 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	skip_whitespace(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	return (j);
}

int	is_image_path(char *line, int j)
{
	return (((line[j] == 'N' && line[j + 1] == 'O')
			|| (line[j] == 'S' && line[j + 1] == 'O')
			|| (line[j] == 'W' && line[j + 1] == 'E')
			|| (line[j] == 'E' && line[j + 1] == 'A')) && line[j + 2] == ' ');
}

int	is_color(char *line, int j)
{
	return ((line[j] == 'F' || line[j] == 'C') && line[j + 1] == ' ');
}

void	parse_elements(t_data *data)
{
	int	i;
	int	j;
	int	el;

	i = 0;
	j = 0;
	el = 0;
	while (i < data->map_height && el < 6 && data->map[i][j] != '1')
	{
		j = skip_whitespace(data->map[i]);
		if (is_image_path(data->map[i], j) && el < 6)
			el += save_img_path(data, data->map[i], data->map[i][j], j + 2);
		else if (is_color(data->map[i], j) && el < 6)
			el += save_colors(data, data->map[i], data->map[i][j], j + 1);
		else if (data->map[i][j] == '\n')
		{
			i++;
			continue ;
		}
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
