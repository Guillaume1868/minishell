/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:01:53 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 14:53:40 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *args, char **envp)
{
	char	*tmp;
	int		i;

	i = 0;
	if (args == NULL)
	{
		while (envp[i] && ft_strncmp("HOME", envp[i], 4) != 0)
			i++;
		tmp = &envp[i][5];
		chdir(tmp);
	}
	else
	{
		while (args[i] != ' ' && args[i] != '\0')
			i++;
		tmp = ft_substr(args, 0, i);
		g_success = 1;
		if (chdir(tmp) != 0)
		{
			g_success = 0;
			printf("cd: %s: No such file or directory\n", args);
		}
		free(tmp);
	}
	return (1);
}

int	ft_help(void)
{
	printf("HELP OF MINISHELL\nThe following are built in: cd help exit\n"
		"Use the man command for information on other programs.\n");
	g_success = 0;
	return (1);
}

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	g_success = 0;
	exit(0);
}

void	ft_env(char	**envp)
{
	int	i;

	g_success = 0;
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
