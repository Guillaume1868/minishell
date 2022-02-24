/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:53:31 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 14:19:48 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;

	i = -1;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (++i < (int)dstsize - 1 && src[i] != '\0' && dst[i] != '\0')
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
