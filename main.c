/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:40 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/07 16:20:39 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	count_lines(char **argv)
{
	int		fd;
	int		lines;
	char	*line;

	if (!check_file_format(argv[1]))
	{
		perror("Map error:");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

int	read_map(t_data *game, char **argv)
{
	char	*line;
	int		lines;
	int		fd;

	lines = count_lines(argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = (char **)malloc(sizeof(char *) * (lines));
	lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		game->map[lines] = line;
		lines++;
	}
	close(fd);
	if (lines == 0)
		return (0);
	game->map_height = lines;
	return (1);
}

void	init_pos(t_data *game, int i, int j)
{
	game->x = 0;
	game->y = 0;
	while (game->map_game[i])
	{
		j = 0;
		while (game->map_game[i][j])
		{
			if (ft_strchr("NSWE", game->map_game[i][j]))
			{
				game->x = j + 0.5;
				game->y = i + 0.5;
				if (game->map_game[i][j] == 'E')
					game->look = 0;
				else if (game->map_game[i][j] == 'N')
					game->look = -M_PI_2;
				else if (game->map_game[i][j] == 'W')
					game->look = M_PI;
				else if (game->map_game[i][j] == 'S')
					game->look = M_PI_2;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	init_img(t_data *game)
{
	t_img	img;
	int		i;

	i = 0;
	while (i < 4)
	{
		img.img = mlx_xpm_file_to_image(game->mlx, game->img_path[i],
				&img.width, &img.height);
		img.addr = (unsigned int *)mlx_get_data_addr(img.img,
				&img.bits_per_pixel, &img.size_line, &img.endian);
		game->images[i] = img;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		error(NULL, "Invalid number of arguments");
	ft_memset(&game, 0, sizeof(t_data));
	read_map(&game, argv);
	parse_map(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	init_img(&game);
	init_img_mm(&game);
	init_pos(&game, 0, 0);
	ft_redraw(&game);
	mlx_hook(game.win, 2, 0, do_move, &game);
	mlx_hook(game.win, 17, 0, (void *)close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

/* make
 ./cub3D maps/map.cub
leaks --atExit -- ./cub3D map.cub
valgrind ./cub3D map.cub
valgrind --leak-check=full --show-leak-kinds=all ./cub3D map.cub


---------------DEBUG----------------

void	print_map(t_data *game)
{
	for (int i = 0; i < game->map_height; i++)
	{
		printf("%s", game->map[i]);
	}
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


 */