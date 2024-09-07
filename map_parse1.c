/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:46 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:29:39 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	save_img_path(t_data *data, char *line, char c, int j)
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

void	save_colors(t_data *data, char *line, char c, int j)
{
	int	i;

	i = j;
	if (c == 'F')
		parse_color(data, line, data->f_colors, &i);
	else if (c == 'C')
		parse_color(data, line, data->c_colors, &i);
}
