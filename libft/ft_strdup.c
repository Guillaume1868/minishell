/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:44:14 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 14:07:58 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*duped;
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	duped = malloc(sizeof(char) * i + 1);
	if (!duped)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		duped[i] = s1[i];
		i++;
	}
	duped[i] = s1[i];
	return (duped);
}
