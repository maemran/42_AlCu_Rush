/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nim_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:35 by maemran           #+#    #+#             */
/*   Updated: 2025/09/06 19:08:10 by maemran          ###   ########.fr       */
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
	free(str);
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
