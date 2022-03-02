/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:18:03 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/02 10:56:39 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], name_len) == 0)
			return (&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}
