/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:29:43 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 15:22:06 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	j;

	dstlen = ft_strlen(dst);
	j = 0;
	if (dstsize <= dstlen)
		return (dstsize + ft_strlen(src));
	while (src[j] && dstlen + j < (dstsize - 1))
	{
		dst[dstlen + j] = src[j];
		j++;
	}
	dst[dstlen + j] = '\0';
	return (ft_strlen(src) + dstlen);
}
