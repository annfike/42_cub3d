/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/06 16:15:15 by adelaloy         ###   ########.fr       */
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

void	save_colors(t_data *data, char *line, char c, int j)
{
	int	i;

	i = j;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (c == 'F')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->f_colors[0] = ft_atoi1(data, &line[i], &i);
		if (line[i++] != ',')
			error(data, "The map is not valid.");
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->f_colors[1] = ft_atoi1(data, &line[i], &i);
		if (line[i++] != ',')
			error(data, "The map is not valid.");
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->f_colors[2] = ft_atoi1(data, &line[i], &i);
		while (line[i] == ' ')
			i++;
		if (line[i] != '\n')
			error(data, "The map is not valid.");
	}
	else if (c == 'C')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->c_colors[0] = ft_atoi1(data, &line[i], &i);
		if (line[i++] != ',')
			error(data, "The map is not valid.");
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->c_colors[1] = ft_atoi1(data, &line[i], &i);
		if (line[i++] != ',')
			error(data, "The map is not valid.");
		if (line[i] < 48 || line[i] > 57)
			error(data, "The map is not valid.");
		data->c_colors[2] = ft_atoi1(data, &line[i], &i);
		while (line[i] == ' ')
			i++;
		if (line[i] != '\n')
			error(data, "The map is not valid.");
	}
}

void	save_map_game(t_data *data, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	data->map_game_width_max = 0;
	data->map_game = (char **)malloc(sizeof(char *) * (data->map_height - i
			+ 1));
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
	printf("Images are valid.\n");
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

static void	print_elements(t_data *data)
{
	printf("\nNO: %s\n", data->img_path[0]);
	printf("SO: %s\n", data->img_path[1]);
	printf("WE: %s\n", data->img_path[2]);
	printf("EA: %s\n", data->img_path[3]);
	printf("F: %d, %d, %d\n", data->f_colors[0], data->f_colors[1],
		data->f_colors[2]);
	printf("C: %d, %d, %d\n", data->c_colors[0], data->c_colors[1],
		data->c_colors[2]);
}

static void	print_map_game(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_game[i])
	{
		printf("%s", data->map_game[i]);
		i++;
	}
}

void	parse_map(t_data *data)
{
	parse_elements(data);
	printf("-----elements-----------\n");
	print_elements(data);
	printf("\n------map_game----------\n");
	print_map_game(data);
	printf("\n-------checking map chars---------\n");
	check_map_chars(data);
	printf("\n----checking walls0------------\n");
	check_walls0(data);
	printf("\n----checking walls------------\n");
	check_walls(data);
	// fill_arr_objects(data);
	// check_valid_path(data);
}
