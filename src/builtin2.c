/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:59:47 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/29 13:22:58 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	g_success = 2;
	if (getcwd(dir, sizeof(dir)) != NULL)
		printf("%s\n", dir);
	else
		perror("pwd() error");
}

void	ft_echo(char **args)
{
	int		i;

	i = 0;
	g_success = 2;
	if (args[1] == 0)
		printf("\n");
	else if (!(args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == 0))
	{
		i++;
		printf("%s", args[i++]);
		while (args[i] != 0)
			printf(" %s", args[i++]);
		printf("\n");
	}
	else
	{
		i += 2;
		printf("%s", args[i++]);
		while (args[i] != 0)
			printf(" %s", args[i++]);
	}
}
