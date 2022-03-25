/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:19:31 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 17:01:20 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_forked(char *cmd, char **args, char **envp)
{
	if (ft_strncmp(cmd, "help", 5) == 0)
		ft_help();
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(args);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(envp);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		pwd();
	else
		return (0);
	return (1);
}

char	**check_builtin(char *cmd, char *args, char **envp)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(args, envp);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit();
	else if (ft_strncmp(cmd, "export", 7) == 0)
		envp = ft_export(envp, args);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		envp = ft_unset(envp, args);
	else
		return (0);
	return (envp);
}

char	**recreate_envp(char **envp, int len, int ismalloc)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (envp[++i])
	{
		res[i] = ft_strdup(envp[i]);
		if (ismalloc == 1)
			free(envp[i]);
	}
	res[i] = 0;
	if (ismalloc == 1)
		free(envp);
	return (res);
}
