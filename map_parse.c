/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:01 by adelaloy          #+#    #+#             */
/*   Updated: 2024/06/08 16:54:26 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"


void    free_map(t_data *data)
{
    int i;

    i = 0;
    while (i < data->map_height)
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
}

void    free_map_game(t_data *data)
{
    int i;

    i = 0;
    while (i < data->map_game_height)
    {
        free(data->map_game[i]);
        i++;
    }
    free(data->map_game);
}

void    free_all(t_data *data)
{
    free_map(data);
    free_map_game(data);
    free(data->img_path[0]);
    free(data->img_path[1]);
    free(data->img_path[2]);
    free(data->img_path[3]);
    //free(data);
}

void    save_img_path(t_data *data, char *line, char c, int j)
{
    int i;
    //printf("line = %s\n", line);
    //printf("c = %c\n", c);
    //printf("j = %d\n", j);

    i = j;
    while (line[i] == ' ' && line[i] != '.' && line[i] != '\0')
        i++;
    char *s = ft_substr(&line[i], 0, ft_strlen(&line[i])-1);
    if (c == 'N')
        data->img_path[0] = ft_strdup(s);
    else if (c == 'S')
        data->img_path[1] = ft_strdup(s);
    else if (c == 'W')
        data->img_path[2] = ft_strdup(s);
    else if (c == 'E')
        data->img_path[3] = ft_strdup(s);
    //free(s);
}

void save_colors(t_data *data, char *line, char c, int j)
{
    int i;
    i = j;
    while ((line[i] < 48 || line[i] > 57) && line[i] != '\0')
        i++;
    if (c == 'F')
    {
        data->f_colors[0] = ft_atoi1(&line[i], &i);
        while (line[i] < 48 || line[i] > 57)
            i++;
        data->f_colors[1] = ft_atoi1(&line[i], &i);
        while (line[i] < 48 || line[i] > 57)
            i++;
        data->f_colors[2] = ft_atoi1(&line[i], &i);
    }     
    else if (c == 'C')
    {
        data->c_colors[0] = ft_atoi1(&line[i], &i);
        while (line[i] < 48 || line[i] > 57)
            i++;
        data->c_colors[1] = ft_atoi1(&line[i], &i);
        while (line[i] < 48 || line[i] > 57)
            i++;
        data->c_colors[2] = ft_atoi1(&line[i], &i);
    }
}

void    save_map_game(t_data *data, int i)
{
    int j;
    int k;

    j = 0;
    k = 0;
    data->map_game = (char **)malloc(sizeof(char *) * (data->map_height - i + 1));
    while (i < data->map_height)
    {
        data->map_game[j] = ft_strdup(data->map[i]);
        i++;
        j++;
        data->map_game_height++;
    }
    data->map_game[j] = NULL;
}

void    parse_elements(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    int elements = 0;
    while (i < data->map_height)
    {
        j = 0;
        while(data->map[i][j] == ' ')
            j++;
        //printf("\nj=%d\n", j);
        if (((data->map[i][j] == 'N' && data->map[i][j+1] == 'O')
            || (data->map[i][j] == 'S' && data->map[i][j+1] == 'O')
            || (data->map[i][j] == 'W' && data->map[i][j+1] == 'E')
            || (data->map[i][j] == 'E' && data->map[i][j+1] == 'A'))
            && elements < 6)
        {
            save_img_path(data, data->map[i], data->map[i][j], j+2);
            elements++;
        }
        else if ((data->map[i][j] == 'F' || data->map[i][j] == 'C')
             && elements < 6)
        {
            //printf("data->map[i][j] = %c\n", data->map[i][j]);
            save_colors(data, data->map[i], data->map[i][j],j+1);
            elements++;
        }
        else if (data->map[i][j] == '\n')
        {
            i++;
            continue;
        }
        
        else if (elements == 6 && data->map[i][j] == '1')
        {
            break;
        }
        
        else
        {
            free_all(data);
            error("The map is not valid.");
        }
        //printf("elements = %d\n", elements);
        i++;
    }
    if (data->img_path[0] == NULL || data->img_path[1] == NULL
        || data->img_path[2] == NULL || data->img_path[3] == NULL)
        error("The map is not valid.");
    save_map_game(data, i);


}

static void    print_elements(t_data *data)
{
    printf("\nNO: %s\n", data->img_path[0]);
    printf("SO: %s\n", data->img_path[1]);
    printf("WE: %s\n", data->img_path[2]);
    printf("EA: %s\n", data->img_path[3]);
    printf("F: %d, %d, %d\n", data->f_colors[0], data->f_colors[1], data->f_colors[2]);
    printf("C: %d, %d, %d\n", data->c_colors[0], data->c_colors[1], data->c_colors[2]);
}

static void  print_map_game(t_data *data)
{
    int i = 0;
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
    
	//fill_arr_objects(data);
	//check_valid_path(data);
}
