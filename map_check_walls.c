/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/06 15:16:50 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_spaces_around(t_data *data, int i, int j)
{
	char	**map;

	map = data->map_game;
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' '
		|| map[i + 1][j] == ' ' || map[i - 1][j + 1] == ' ' || map[i - 1][j
		- 1] == ' ' || map[i + 1][j + 1] == ' ' || map[i + 1][j - 1] == ' ')
	{
		error(data, "The map is not surrounded by walls.");
	}
	if (map[i][j - 1] == '\n' || map[i][j + 1] == '\n' || map[i - 1][j] == '\n'
		|| map[i + 1][j] == '\n' || map[i - 1][j + 1] == '\n' || map[i - 1][j
		- 1] == '\n' || map[i + 1][j + 1] == '\n' || map[i + 1][j - 1] == '\n')
	{
		error(data, "The map is not surrounded by walls.");
	}
}

void	check_walls0(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (i < data->map_game_height)
	{
		j = 0;
		len = ft_strlen(data->map_game[i]);
		while (data->map_game[i][j] != '\n' && data->map_game[i][j] != '\0')
		{
			if (ft_strchr("0NSWE", data->map_game[i][j]))
			{
				if ((i == 0 || i == data->map_game_height - 1) || (j == 0
						|| j == len - 1))
				{
					error(data, "The map is not surrounded by walls.");
				}
				check_spaces_around(data, i, j);
			}
			j++;
		}
		i++;
	}
}

static int	check_wall_cell(t_data *data, int i, int k, int flag)
{
	if (!ft_strchr("10NSWE", data->map_game[i][k]))
		flag = 0;
	else if (data->map_game[i][k] == '1')
		flag = 1;
	return (flag);
}

static int	check_wall_all_dir(t_data *data, int i, int j, int len)
{
	int	k;
	int	flag;
	int	flag1;

	k = -1;
	flag = 0;
	flag1 = 0;
	while (j > ++k) //слева
		flag = check_wall_cell(data, i, k, flag);
	flag1 = flag;
	k = len + 1;
	while (j < --k) //справа
		flag = check_wall_cell(data, i, k, flag);
	flag1 += flag;
	k = -1;
	while (i > ++k) //сверху
		flag = check_wall_cell(data, k, j, flag);
	flag1 += flag;
	k = data->map_game_height - 1 + 1;
	while (i < --k) //снизу
		flag = check_wall_cell(data, k, j, flag);
	flag1 += flag;
	return (flag1);
}

void	check_walls(t_data *data)
{
	int	i;
	int	j;
	int	flag1;
	int	len;

	i = 1;
	j = 0;
	flag1 = 0;
	while (i < data->map_game_height - 1)
	{
		len = ft_strlen(data->map_game[i]) - 1;
		j = 0;
		while (data->map_game[i][j] != '\n' && data->map_game[i][j] != '\0')
		{
			if (ft_strchr("0NSWE", data->map_game[i][j]))
			{
				flag1 = check_wall_all_dir(data, i, j, len);
				if (flag1 < 4)
				{
					error(data, "The map is not surrounded by walls.");
				}
			}
			j++;
		}
		i++;
	}
}
