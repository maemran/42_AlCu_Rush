/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:39 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/06 20:19:57 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"

int heaps_num(char *file, t_game *data)
{
    int count;
    char    *str;
	int fd;
    
    count = 0;
	data->file = file;
    fd = open(file, O_RDONLY);
    str = get_next_line(fd);
    while (str)
    {
        if (str[0] == '\n')
        {
			close(fd);
			free(str);
            ft_putstr_fd("ERROR\n", 2);
            return (-1);
        }
        free(str);
        str = get_next_line(fd);
        count++;
    }
    free(str);
	if (fd != -1)
		close(fd);
    return (count);
}

int  read_from_user(t_game *data)
{
    char *str;
    int size;
	int fd;

    fd = open("t.text", O_WRONLY | O_TRUNC | O_CREAT, 0777);
    while (1)
    {
        str = get_next_line(0);
        if (str[0] == '\n')
            break;
        ft_putstr_fd(str, fd);
        free(str);
    }
    free(str);
    close (fd);
    size = heaps_num("t.text", data);
	if (size == -1)
		return (-1);
	data->file = "t.text";
    return (size);
}

int	store_file(t_game *data)
{
	int fd;
	char *str;
	int i;
	
	i = 0;
	data->map = malloc(sizeof(char *) * (data->size + 1));
	if (!data->map)
		return (0);
	fd = open(data->file, O_RDONLY);
    str = get_next_line(fd);
    while (str)
    {
        if ((ft_strlen(str) - 1) != 0)
            str[ft_strlen(str) - 1] = '\0';
        data->map[i] = str;
        str = get_next_line(fd);
        i++;
    }
    data->map[i] = NULL;
	close(fd);
	return (1);
}

int  add_list(t_game *data)
{
    int i;

    i = 1;
	data->lst = ft_lstnew(ft_atoi(data->map[0]));
	if (!data->lst)
		return (0);
    while (data->map[i])
    {
        add_node(&data->lst, ft_atoi(data->map[i]));
        i++;
    }
	return (1);
}

int	line_check(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int    change_to_num(t_game *data)
{
    int j;
    int i;
	int flag;
    int count;
    

    j = 0;
    i = 0;
    count = 0;
	flag = 0;
    while (data->map[i])
    {
		if (!line_check(data->map[i]))
			break;
        j = 0;
        count = 0;
        while (data->map[i][j])
        {
            if(data->map[i][j] == '|')
                count++;
            j++;
        }
		if (flag == 0)
		{
			data->lst = ft_lstnew(count);
			if (!data->lst)
				return (0);
			flag = 1;
			i++;
			continue;
		}
        add_node(&data->lst, count);
        i++;
    }
	return (1);
}

int main(int argc, char **argv)
{
    t_game *data;
    int i;
    int type;
	
    i = 0;
    type = 0;
    data = malloc(sizeof(t_game));
	if (!data)
		return (1);
    if (argc == 1)
        data->size = read_from_user(data);
    else if (argc == 2)
        data->size = heaps_num(argv[1], data);
    else
    {
		free(data);
        write(2, "ERROR\n", 6);
        return (1);
    }
	if (data->size == -1 || data->size == 0)
	{
		free(data);
		return (1);
	}
	if (!store_file(data))
		return (1);
    if (check_map(data, &type))
        return (1);
    if (type == 1)
	{
        if (!change_to_num(data))
			return (1);
	}
    if (type == 2)
	{
		if (!add_list(data))
			return (1);
	}
    print_heaps(data->lst);
    game(data);
	ft_free_tow_d_array(data->map);
	free(data);
	return (0);
}
