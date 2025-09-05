/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:39 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/05 20:49:21 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"


// void game()
// {
//     while ()
// }
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	length;

	length = 0;
	while (s[length] != 0)
	{
		ft_putchar_fd(s[length], fd);
		length++;
	}
}

void	print_map(char **array, int *type)
{
	int		length;
    int num;
    int i;
    int j;

	length = 0;
    i = 1;
    j = 1;
    if (*type == 1)
    {
        while (array[length])
        {
            ft_putstr_fd(array[length], 1);
            length++;
        }       
    }
    if (*type == 2)
    {
        while (array[length])
        {
            j++;
            num = atoi(array[length]);
            while (num > 0)
            {
                write (1, "| ", 2);
                num--;
            }
            write (1, "\n", 1);
            while (i > 0)
            {
                write (1, " ", 1);
                i--;
            }
            i = j;
            length++;
        }
    }
}

int check_map(char **map, int *type)
{
    int i;
    int j;
    int flag_num;
    int flag_pipe;

    j = 0;
    i = 0;
    flag_num = 0;
    flag_pipe = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (map[i][j] > '0' && map[i][j] < '9')
                flag_num = 1;
            else if (map[i][j] == '|' || map[i][j] == ' ')
                flag_pipe = 1;
            else
            {
                write(2, "ERROR\n", 6);
                return (1);
            }
        }
    }
    if (flag_num == 1 && flag_pipe == 1)
    {
        write(2, "ERROR\n", 6);
        return (1);
    }
    if (flag_num == 1)
    {
        while (map[i])
        {
            if (atoi(map[i]) > 10000 || atoi(map[i]) < 1)
            {
                write(2, "ERROR\n", 6);
                return (1);
            }
        }
    }
    if (flag_pipe == 1)
        *type = 1;
    if (flag_num == 1)
        *type = 2;
    return (0);
}

int heaps_num(char *file, t_game *data)
{
    int count;
    char    *str;
    
    count = 0;
    data->fd = open(file, O_RDONLY);
    str = get_next_line(data->fd);
    while (str)
    {
        if (str[0] == '\n')
            return (-1);
        free(str);
        str = get_next_line(data->fd);
        count++;
    }
    free(str);
    return (count);
}

int  read_from_user(t_game *data)
{
    char *str;
    int size;

    data->fd = open("t.text", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    while (1)
    {
        str = get_next_line(0);
        if (str[0] == '\n')
            break;
        ft_putstr_fd(str, data->fd);
        free(str);
    }
    free(str);
    close (data->fd);
    size = heaps_num("t.text", data);
    return (size);
}

int main(int argc, char **argv)
{
    char **map;
    t_game *data;
    int i;
    char *str;
    // int type;
    int size;

    i = 0;
    // type = 0;
    data = malloc(sizeof(data));
    data->fd = 0;
    if (argc == 1)
        size = read_from_user(data);
    else if (argc == 2)
        size = heaps_num(argv[1], data);
    else
    {
        write(2, "ERROR\n", 6);
        return (1);
    }
    if (size == -1 || size == 0)
        return (1); 
    map = malloc(sizeof(char *) * size + 1);
    printf("size: %i\n fd: %i\n", size, data->fd);
    int fd = open("t.txt", O_RDONLY);
    str = get_next_line(fd);
    printf("%s\n", str);
    while (str)
    {
        map[i] = str;
        str = get_next_line(data->fd);
        i++;
    }
    map[i] = NULL;
       
    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
    // if (check_map(map, &type))
    //     return (1);
    // print_map(map, &type);
    
    
}
