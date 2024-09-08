/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:46 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 17:26:35 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	save_img_path(t_data *data, char *line, char c, int j)
{
	int		i;
	char	*s;

	i = j;
	while (line[i] == ' ' && line[i] != '.' && line[i] != '\0')
		i++;
	s = ft_substr(&line[i], 0, ft_strlen(&line[i]) - 1);
	if (c == 'N')
		data->img_path[0] = ft_strdup(s);
	else if (c == 'S')
		data->img_path[1] = ft_strdup(s);
	else if (c == 'W')
		data->img_path[2] = ft_strdup(s);
	else if (c == 'E')
		data->img_path[3] = ft_strdup(s);
	free(s);
	return (1);
}

static void	parse_color(t_data *data, char *line, int *color_array, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] < '0' || line[*i] > '9')
		error(data, "The map is not valid.");
	color_array[0] = ft_atoi1(data, &line[*i], i);
	if (line[(*i)++] != ',')
		error(data, "The map is not valid.");
	if (line[*i] < '0' || line[*i] > '9')
		error(data, "The map is not valid.");
	color_array[1] = ft_atoi1(data, &line[*i], i);
	if (line[(*i)++] != ',')
		error(data, "The map is not valid.");
	if (line[*i] < '0' || line[*i] > '9')
		error(data, "The map is not valid.");
	color_array[2] = ft_atoi1(data, &line[*i], i);
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] != '\n')
		error(data, "The map is not valid.");
}

int	save_colors(t_data *data, char *line, char c, int j)
{
	int	i;

	i = j;
	if (c == 'F')
		parse_color(data, line, data->f_colors, &i);
	else if (c == 'C')
		parse_color(data, line, data->c_colors, &i);
	return (1);
}

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
