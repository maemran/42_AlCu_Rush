/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:55:43 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/06 16:20:23 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nim.h"

void	ft_free_tow_d_array(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		string[i] = NULL;
		i++;
	}
	free(string[i]);
	free(string);
}

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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}