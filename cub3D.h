/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:27:23 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/29 18:30:01 by dmiasnik         ###   ########.fr       */
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
	int		map_width;
    void    *mlx;
	void    *win;
    void    *img_floor;
    void    *img_wall;
    void    *img_player;
    void    *img_to_collect;
    void    *img_exit;
    int     player_x;
    int     player_y;
    int     moves_count;
    int     to_collect_count;
    int    **objects;

}	t_data;

/* utils */
void	*ft_memset(void *s, int c, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

void	ft_reload(t_data *game);

#endif