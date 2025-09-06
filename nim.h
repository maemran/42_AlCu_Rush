/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:32 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/06 09:42:17 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIM_H
#define NIM_H

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_game
{
	char	*file;
	char	**map;
	int		size;
} t_game;

#endif