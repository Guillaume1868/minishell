/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:25:10 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/12 10:13:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		res = (char *) malloc(sizeof(char));
		res[0] = '\0';
		return (res);
	}
	res = (char *) malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while ((unsigned long)++i < len && s[i] + start != '\0')
		res[i] = s[i + start];
	res[i] = '\0';
	return (res);
}
