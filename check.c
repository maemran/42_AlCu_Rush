/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:57:44 by maemran           #+#    #+#             */
/*   Updated: 2025/09/14 23:24:53 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"

int check_map(t_game *data, int *type)
{
    int i;
    int j;
    int flag_num;
    int flag_pipe;

    j = 0;
    i = 0;
    flag_num = 0;
    flag_pipe = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if ((data->map[i][j] >= '0' && data->map[i][j] <= '9'))
                flag_num = 1;
            else if (data->map[i][j] == '|' || data->map[i][j] == ' ')
                flag_pipe = 1;
            else
            {
                ft_free_tow_d_array(data->map);
                free(data);
                write(2, "ERROR\n", 6);
                return (1);
            }
            j++;
        }
        i++;
    }
    if (flag_num == 1 && flag_pipe == 1)
    {
        ft_free_tow_d_array(data->map);
        free(data);
        write(2, "ERROR\n", 6);
        return (1);
    }
    i = 0;
    if (flag_num == 1)
    {
        while (data->map[i])
        {
            if (ft_atoi(data->map[i]) > 10000 || ft_atoi(data->map[i]) < 1)
            {
                ft_free_tow_d_array(data->map);
                free(data);
                write(2, "ERROR\n", 6);
                return (1);
            }
            i++;
        }
    }
    if (flag_pipe == 1)
        *type = 1;
    if (flag_num == 1)
        *type = 2;
    return (0);
}
