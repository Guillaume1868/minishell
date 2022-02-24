/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:52:10 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 13:12:49 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	if (dst <= src)
	{
		ft_memcpy(dst, src, len);
		return (dst);
	}
	d = (char *) dst - 1;
	s = (char *)src - 1;
	while (len != 0)
	{
		d[len] = s[len];
		len--;
	}
	return (dst);
}
