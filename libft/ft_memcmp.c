/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:47:03 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 12:52:45 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = -1;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (++i < (int)n)
	{
		if (a[i] == b[i])
			;
		else
			return (a[i] - b[i]);
	}
	return (0);
}
