/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/06/01 14:41:50 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

static int	check_cell_char(t_data *data, int i, int j)
{
    int player_count=0;
    if (!ft_strchr(" 01NSWE", data->map_game[i][j]))
	{
		free_all(data);
		error("The map contains invalid characters.");
	}
    if (ft_strchr("NSWE", data->map_game[i][j]))
		player_count++;
    return (player_count);
}

void	check_map_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
    int player_count=0;
	while (i < data->map_game_height)
	{
        //printf("i = %d\n", i);
		j = 0;
		while (data->map_game[i][j] != '\n' && data->map_game[i][j] != '\0')
		{
            //printf("j = %d\n", j);
            //printf("data->map_game[i][j] = %c\n", data->map_game[i][j]);
			player_count += check_cell_char(data, i, j);
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		free_all(data);
		error("Map error.");
	}
}




