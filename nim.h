/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:32 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/06 20:03:11 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIM_H
#define NIM_H

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
	int content;
	struct s_list	*next;
}	t_list;

typedef struct s_game
{
	char	*file;
	char	**map;
	int		size;
	int		player_flag;
	int		ai_matches;
	t_list	*lst;
} t_game;

t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void    remove_last_node(t_list **lst);
void	add_node(t_list **lst, int content);
void	print_heaps(t_list *head);
void	ft_free_tow_d_array(char **string);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int    change_to_num(t_game *data);
int		check_move(int matches, t_list *node);
void    ai_move(t_game *data);
int     check_input(char *str);
void    player_move(t_game *data);
void	game(t_game *data);
int		check_map(t_game *data, int *type);

#endif