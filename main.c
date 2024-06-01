/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:40 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/31 15:33:30 by adelaloy         ###   ########.fr       */
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

int	do_move(int key, t_data *game)
{
	if (key == KEYEXIT)
		close_game(game);
	/*# define KEYUP 126
	# define KEYDOWN 125
	# define KEYRIGHT 124
	# define KEYLEFT 123*/
	/*
	else if (key == 123)
		step_up(par, par->i - 1);
	if (key == 124)
		step_up(par, par->i + 1);
	if (key == 125)
		step_up(par, par->i + par->x + 1);
	if (key == 126)
		step_up(par, par->i - par->x - 1);
	*/
	(void)game;
	return (1);
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
	ft_redraw(&game);
	mlx_key_hook(game.win, do_move, &game);
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