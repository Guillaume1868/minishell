/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:48:38 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/08 11:57:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		++i;
	return (i);
}

size_t	ft_strlen_env(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	return (i);
}
