/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:57:29 by maemran           #+#    #+#             */
/*   Updated: 2025/09/06 19:18:38 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t	length;
	char	*ptr;

	length = 0;
	ptr = (char *)s;
	while (length < n)
	{
		ptr[length] = '\0';
		length++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		length;
	char		*ptr1;
	const char	*source;

	length = 0;
	ptr1 = (char *)dest;
	source = (const char *)src;
	if (!ptr1 && !source)
		return (NULL);
	while (length < n)
	{
		ptr1[length] = source[length];
		length++;
	}
	return (ptr1);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}
