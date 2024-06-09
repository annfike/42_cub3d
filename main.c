/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:40 by adelaloy          #+#    #+#             */
/*   Updated: 2024/06/09 15:33:46 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_format(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] == 'b' && s[i - 2] == 'u' && s[i - 3] == 'c' && s[i
		- 4] == '.')
		return (1);
	return (0);
}

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

void print_map(t_data *game) {
    for (int i = 0; i < game->map_height; i++) {
        printf("%s", game->map[i]);
    }
}


void	error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void	close_game(t_data *game){
	(void)game;
	exit(0);
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
	dist = ft_ray(game, ft_sign(dy) * M_PI / 2);
	if (dist * dist < dy * dy)
		dy = 0.0f;
	dist = ft_ray(game, (1 - (ft_sign(dx) + 1) / 2) * M_PI);
	if (dist * dist < dx * dx)
		dx = 0.0f;
	dist = ft_ray(game, angle);
	if (dist * dist < dy * dy + dx * dx)
		if (ft_sign(dy) * ft_sign(dx) != 0)
			dy = 0.0f;
	game->x += dx;
	game->y -= dy;
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
		game->look += STEP_TURN;
	else if (key == KEYRIGHT)
		game->look -= STEP_TURN;
	else if (key == KEYA)
		ft_move(game, 3);
	else if (key == KEYD)
		ft_move(game, 1);
	else 
		return (1);
	ft_redraw(game);
	return (1);
}

void	init_pos(t_data *game, int i, int j)
{
	game->x = 0;
	game->y = 0;
	while (game->map_game[i])
	{
		j = 0;
		while(game->map_game[i][j])
		{
			if (ft_strchr("NSWE", game->map_game[i][j]))
			{
				game->x = j + 0.5;
				game->y = i + 0.5;
				if (game->map_game[i][j] == 'E')
					game->look = 0;
				else if (game->map_game[i][j] == 'N')
					game->look = M_PI_2;
				else if (game->map_game[i][j] == 'W')
					game->look = M_PI;
				else if (game->map_game[i][j] == 'S')
					game->look = -0.5 * M_PI;
				break;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		error("Invalid number of arguments");
	ft_memset(&game, 0, sizeof(t_data));
	read_map(&game, argv);
	printf("\n-----full map parsed-----------\n");
	print_map(&game);
	parse_map(&game);
	//check_map(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	init_pos(&game, 0, 0);
	ft_redraw(&game);
	mlx_do_key_autorepeaton(game.mlx);
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
 */