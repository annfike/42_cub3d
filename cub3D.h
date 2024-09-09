/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:27:23 by adelaloy          #+#    #+#             */
/*   Updated: 2024/09/09 12:21:59 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

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
# define KEYM 46

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define FOV 1.047197551196598 
# define STEP_TURN 0.069813170079773 
/*
# define FOV 60 * M_PI / 180
# define STEP_TURN 4.0f * M_PI / 180
*/
# define STEP_UP 0.2f
# define MM_SIZE 8

typedef struct s_img
{
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_data
{
	char			**map;
	int				map_height;
	char			*img_path[4];
	int				f_colors[3];
	int				c_colors[3];
	char			**map_game;
	int				map_game_height;
	int				map_game_width_max;
	void			*mlx;
	void			*win;
	float			x;
	float			y;
	float			look;
	t_img			images[4];
	int				txt_idx;
	float			txt_w;
	t_img			mm_player;
	t_img			mm_wall;
	int				mm_show;
}					t_data;

/* main */
int					count_lines(char **argv);
int					read_map(t_data *game, char **argv);
void				init_pos(t_data *game, int i, int j);
void				init_img(t_data *game);

/* utils */
void				*ft_memset(void *s, int c, size_t n);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi1(t_data *data, const char *str, int *i);

/* free */
void				free_map(t_data *data);
void				free_map_game(t_data *data);
void				free_all(t_data *data);
void				error(t_data *game, char *error);
void				close_game(t_data *game);

/* move */
void				ft_move(t_data *game, int direction);
int					do_move(int key, t_data *game);

/* map_parse */
int					save_img_path(t_data *data, char *line, char c, int j);
int					save_colors(t_data *data, char *line, char c, int j);
void				save_map_game(t_data *data, int i);
void				parse_elements(t_data *data);
void				parse_map(t_data *data);

/* map_check */
int					check_file_format(char *s);
void				check_map_chars(t_data *data);
void				check_map(t_data *data);
void				check_map0(t_data *data);
void				check_imgs(t_data *data);

/* map_check_walls */
void				check_walls(t_data *data);
void				check_walls0(t_data *data);

/* draw */
void				ft_redraw(t_data *game);
void				draw_line(t_data *game, int w, float dist, t_img img);
float				ft_ray(t_data *game, float look);

/* bonus */
void				init_img_mm(t_data *game);
void				print_mm(t_data *game);

#endif