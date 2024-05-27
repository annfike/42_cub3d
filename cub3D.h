/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:27:23 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/26 17:34:40 by adelaloy         ###   ########.fr       */
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

typedef struct s_data
{
    char	**map;
	int		map_height;
	int		map_width;
    void    *mlx_ptr;
	void    *win_ptr;
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


#endif