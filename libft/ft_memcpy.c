/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:13:40 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 13:12:57 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	int		i;
	char	*ptrsrc;
	char	*ptrdst;

	if (!dst && !src)
	{
		return (NULL);
	}
	ptrsrc = (char *) src;
	ptrdst = (char *) dst;
	i = -1;
	while (++i < (int) len)
	{
		*(ptrdst + i) = *(ptrsrc + i);
	}
	return (dst);
}
