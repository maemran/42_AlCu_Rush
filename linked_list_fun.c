/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:50:39 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/14 23:26:01 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"

t_list	*ft_lstnew(int content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = *lst;
	if (new == NULL)
		return ;
	if (lst == NULL)
		return ;
	if (node == NULL)
	{
		*lst = new;
		return ;
	}
	node = ft_lstlast(*lst);
	node->next = new;
}

void	add_node(t_list **lst, int content)
{
	t_list *node;
	
	node = ft_lstnew(content);
	ft_lstadd_back(lst , node);
}

void    remove_last_node(t_list **lst)
{
    t_list  *head;
    t_list  *last;

    if ((*lst)->next == NULL)
    {
        free(*lst);
        *lst = NULL;
        return ;
    }
    head = *lst;
    while ((*lst)->next->next != NULL)
        *lst = (*lst)->next;
    last = (*lst)->next;
    (*lst)->next = NULL;
    free(last);
    *lst = head;
}

void	print_heaps(t_list *head)
{
	int row = 0;
    while (head) 
	{
        for (int i = 0; i < row; i++)
			write(1, " ", 1);
        for (int i = 0; i < head->content; i++)
			write(1, "| ", 2);
		write(1, "\n", 1);
        row++;
        head = head->next;
    }
}