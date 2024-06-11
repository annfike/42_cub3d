/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:27:23 by adelaloy          #+#    #+#             */
/*   Updated: 2024/06/11 17:01:01 by adelaloy         ###   ########.fr       */
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
# define KEYW 13
# define KEYA 0
# define KEYS 1
# define KEYD 2

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define FOV 90
# define STEP_TURN 4.0f * M_PI / 180
# define STEP_UP 0.2f

typedef struct s_img
{
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}	t_img;

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

	float	x;
	float	y;
	float	look;
	t_img	images[4];
    int txt_idx;
    float txt_w;
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

typedef struct s_ray
{
	float	dx;
	float	dy;
	int		sx;
	int		sy;
	float	hor_x;
	float	hor_y;
	float	vert_x;
	float	vert_y;
	float	vert_dist;
	float	hor_dist;
	float	vert_w;
	float	hor_w;
}	t_ray;

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
void    check_map_chars(t_data *data);

/* map_check_walls */
void    check_walls(t_data *data);
void	check_walls0(t_data *data);

/* draw */
void	ft_redraw(t_data *game);
void	draw_line(t_data *game, int w, float dist, t_img img);
float	ft_ray(t_data *game, float look);
int		ft_sign(float f);

#endif