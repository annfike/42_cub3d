/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 17:22:56 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_format(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] == 'b' && s[i - 2] == 'u'
		&& s[i - 3] == 'c' && s[i - 4] == '.')
		return (1);
	return (0);
}

static int	check_cell_char(t_data *data, int i, int j)
{
	int	player_count;

	player_count = 0;
	if (!ft_strchr(" 01NSWE", data->map_game[i][j]))
	{
		error(data, "Map error.");
	}
	if (ft_strchr("NSWE", data->map_game[i][j]))
		player_count++;
	return (player_count);
}

void	check_map_chars(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (i < data->map_game_height)
	{
		j = 0;
		while (data->map_game[i][j] != '\n' && data->map_game[i][j] != '\0')
		{
			player_count += check_cell_char(data, i, j);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		error(data, "Map error.");
}

void	check_imgs(t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->img_path[i] == NULL)
			error(data, "The map is not valid.");
		fd = open(data->img_path[i], O_RDONLY);
		if (fd < 0)
			error(data, "The map is not valid.");
		close(fd);
		i++;
	}
}
