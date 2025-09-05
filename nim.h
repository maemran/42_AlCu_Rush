/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:31:32 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/05 20:26:56 by salshaha         ###   ########.fr       */
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
    int fd;
} t_game;

#endif