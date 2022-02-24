/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:29:45 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/13 11:51:20 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*start(char *s1, char const *set)
{
	int	i;
	int	j;

	j = -1;
	while (s1[++j])
	{
		i = -1;
		while (set[++i])
		{
			if (set[i] == s1[j])
				break ;
		}
		if (set[i] == 0 || s1[j] == 0)
			return (&s1[j]);
	}
	return (&s1[j]);
}

static char	*end(char *s1, char const *set)
{
	int	i;
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(s1) - 1;
	while (s1[++j])
	{
		i = -1;
		while (set[++i])
		{
			if (set[i] == s1[len - j])
				break ;
		}
		if (!set[i])
		{
			s1[len - j + 1] = '\0';
			return (s1);
		}
	}
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*origin;
	char	*ret;

	if (s1 == 0)
		return (NULL);
	s = ft_strdup(s1);
	origin = s;
	if (s == 0)
		return (0);
	s = start(s, set);
	s = end(s, set);
	ret = ft_strdup(s);
	if (ret == 0)
		return (0);
	free(origin);
	return (ret);
}
