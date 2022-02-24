/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:25:53 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 12:40:10 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*haystack;

	i = -1;
	haystack = (unsigned char *)s;
	while (1)
	{
		if (++i >= (int) n)
			return (NULL);
		if (haystack[i] == (unsigned char) c)
			return ((void *)&haystack[i]);
	}
}
