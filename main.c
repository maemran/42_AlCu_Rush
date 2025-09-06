/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:39 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/06 18:17:23 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"

int check_move(int matches, t_list *node)
{
    if (matches > node->content)
        return (0);
    return (1);
}

void    ai_move(t_game *data) 
{
    t_list  *node;

    data->player_flag = 0;
    node = ft_lstlast(data->lst);
    data->ai_matches = node->content;
    if ((node->content % 4 == 1) || (node->content % 4 == 0))
    {
        node->content -= 1;
        data->ai_matches = 1;
    }
    else
    {
        if (check_move(((node->content - 1) % 4), node))
            node->content = node->content - (node->content - 1) % 4;
        data->ai_matches = (data->ai_matches - 1) % 4;
    }
    if (node->content == 0)
        remove_last_node (&data->lst);
}

int     check_input(char *str)
{
    int i;
    int num;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '3'))
        {
            ft_putstr_fd("Invalid choice\n", 2);
            return (-1);
        }
        i++;
    }
    num = ft_atoi(str);
    if (!(num >= 1 && num <= 3))
    {
        ft_putstr_fd("Invalid choice\n", 2);
        return (-1);
    }
    return (num);
}
            
void    player_move(t_game *data)
{
    int flag;
    char    *str;
    int num;
    t_list  *node;

    flag = 1;
    data->player_flag = 1;
    node = ft_lstlast(data->lst);
    ft_putstr_fd("Please choose between 1 and 3 items\n", 1);
    str = get_next_line(0);
    str[ft_strlen(str) - 1] = '\0';
    while (flag)
    {
        num = check_input(str);
        if (num == -1)
        {
            free(str);
            ft_putstr_fd("Please choose between 1 and 3 items\n", 1);
            str = get_next_line(0);
            str[ft_strlen(str) - 1] = '\0';
        }
        else if (!check_move(num, node))
        {
            free(str);
            ft_putstr_fd("Invalid choice\n", 2);
            ft_putstr_fd("Please choose between 1 and 3 items\n", 1);
            str = get_next_line(0);
            str[ft_strlen(str) - 1] = '\0';
        }
        else
            flag = 0;
    }
    node->content -= num;
    if (node->content == 0)
        remove_last_node (&data->lst);
}
                                
void game(t_game *data)
{
    char num;

    while (data->lst)
    {
        ft_putstr_fd("\033[32mAI turn\033[0m\n", 1);
        ai_move(data);
        if (!data->lst)
            break;
        num = data->ai_matches + '0';
        print_heaps(data->lst);
        ft_putstr_fd("\n", 1);
        ft_putstr_fd("AI took ", 1);
        write(1, &num, 1);
        ft_putstr_fd("\n", 1);
        ft_putstr_fd("\033[31mplayer turn\033[0m\n", 1);
        player_move(data);
        print_heaps(data->lst);
        ft_putstr_fd("\n", 1);
    }
    if (data->player_flag == 1)
        ft_putstr_fd("\nYou are lose!\n", 1);
    else
        ft_putstr_fd("\nYou are the winner! Congratulations!\n", 1);
}

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
            if ((data->map[i][j] > '0' && data->map[i][j] < '9'))
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
            ft_putstr_fd("ERROR\n", 2);
            return (-1);
        }
        free(str);
        str = get_next_line(fd);
        count++;
    }
    free(str);
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
	data->file = "t.text";
    return (size);
}

void	store_file(t_game *data)
{
	int fd;
	char *str;
	int i;
	
	i = 0;
	data->map = malloc(sizeof(char *) * (data->size + 1));
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
}

void add_list(t_game *data)
{
    int i;

    i = 1;
	data->lst = ft_lstnew(ft_atoi(data->map[0]));
    while (data->map[i])
    {
        add_node(&data->lst, ft_atoi(data->map[i]));
        i++;
    }
}

void    change_to_num(t_game *data)
{
    int j;
    int i;
    int count;
    

    j = 0;
    i = 0;
    count = 0;
    while (data->map[i])
    {
        j = 0;
        count = 0;
        while (data->map[i][j])
        {
            if(data->map[i][j] == '|')
                count++;
            j++;
        }
        add_node(&data->lst, count);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_game *data;
    int i;
    int type;
	
    i = 0;
    type = 0;
    data = malloc(sizeof(t_game));
    if (argc == 1)
        data->size = read_from_user(data);
    else if (argc == 2)
        data->size = heaps_num(argv[1], data);
    else
    {
        write(2, "ERROR\n", 6);
        return (1);
    }
	if (data->size == -1 || data->size == 0)
		return (1);
	store_file(data);
    if (check_map(data, &type))
        return (1);
    // print_map(data, &type);
    if (type == 1)
        change_to_num(data);
    if (type == 2)
        add_list(data);
    print_heaps(data->lst);
    game(data);
}


//  Fix last problem          ✅
//  
//  convert char **map to array of integers ->  two dimensional array of integer ✅
//
//  take input from user
//
//  handle input taken from user like -> more than 3 , just nums
//
//  using AI function
//
//  put this code in infinite loop that wait the winner