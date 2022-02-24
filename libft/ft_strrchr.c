/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:26:18 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 13:31:57 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;

	i = ft_strlen(s);
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	while (--i >= 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
