/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:27:23 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/30 15:42:22 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

# define SIZE 40
# define KEYUP 126
# define KEYDOWN 125
# define KEYRIGHT 124
# define KEYLEFT 123
# define KEYEXIT 53

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef struct s_data
{
	char	**map;
	int		map_height;
    char    *img_path[4]; //NSWE
    int     f_colors[3];
    int     c_colors[3];
    char	**map_game;
    int		map_game_height;
	void    *mlx;
	void    *win;
    
    /*
    void    *img_floor;
    void    *img_wall;
    void    *img_player;
    void    *img_to_collect;
    void    *img_exit;
    int     player_x;
    int     player_y;
    int     moves_count;
    int     to_collect_count;
    int    **objects;*/

}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

/* main */
void	error(char *error);

/* utils */
void	*ft_memset(void *s, int c, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int     ft_atoi1(const char *str, int *i);

/* map_parse */
void    free_map(t_data *data);
void    free_all(t_data *data);
void    save_img_path(t_data *data, char *line, char c, int j);
void    save_colors(t_data *data, char *line, char c, int j);
void    save_map_game(t_data *data, int i);
void    parse_elements(t_data *data);
void    parse_map(t_data *data);

/* map_check */
int     check_cell_char(t_data *data, int i, int j);
void    check_map_chars(t_data *data);

/* draw */
void	ft_redraw(t_data *game);

#endif