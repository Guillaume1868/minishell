/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:19:31 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/29 17:07:45 by gaubert          ###   ########.fr       */
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

char	**check_builtin(char *cmd, char *args, char **envp, t_exec *exec)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(args, envp);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(envp, exec);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		envp = ft_export(envp, args);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		envp = ft_unset(envp, args, exec);
	else if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "help", 5)
		== 0 || ft_strncmp(cmd, "env", 4) == 0 || ft_strncmp(cmd, "pwd", 4)
		== 0)
	{
		if (exec->last_success == 0)
		{
			exec->last_success = g_success;
			g_success = 2;
		}
		else
			g_success = exec->last_success;
		return (0);
	}
	else
		return (0);
	return (envp);
}

char	**recreate_envp(char **envp, int len, int ismalloc)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (len + 2));
	if (res == 0)
	{
		if (ismalloc == 1)
			free_envp(envp);
		return (0);
	}
	i = -1;
	while (envp[++i])
		res[i] = ft_strdup(envp[i]);
	res[len + 1] = 0;
	if (ismalloc == 1)
		free_envp(envp);
	return (res);
}

char	**make_export(char **envp, char *args, char *tmp, int i)
{
	int	j;

	j = 0;
	if (envp[i])
	{
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		tmp = ft_substr(envp[i], 0, j);
		j = 0;
		while (args[j] && args[j] != '=')
			j++;
		envp[i] = ft_strjoinfree(tmp, &args[j]);
	}
	else
	{
		i = 0;
		while (envp[i])
			i++;
		i++;
		envp = recreate_envp(envp, i, 1);
		if (tmp)
			envp[i - 1] = ft_strdup(args);
		envp[i] = 0;
	}
	return (envp);
}
