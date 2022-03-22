/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:01:53 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/21 14:35:58 by gaubert          ###   ########.fr       */
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
		if (chdir(tmp) != 0)
			printf("cd: %s: No such file or directory\n", args);
		free(tmp);
	}
	return (1);
}

int	ft_help(void)
{
	printf("HELP OF MINISHELL\nThe following are built in: cd help exit\n"
		"Use the man command for information on other programs.\n");
	return (1);
}

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	ft_env(char	**envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	check_builtin_forked(char *cmd, char *args, char **envp)
{
	if (ft_strncmp(cmd, "help", ft_strlen(cmd)) == 0)
		ft_help();
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		ft_echo(args);
	/*else if (ft_strncmp(cmd, "$", 1) == 0)
		printf("%s\n", get_env(cmd + 1, envp));*/
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		ft_env(envp);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		pwd();
	else
		return (0);
	return (1);
}

char	**check_builtin(char *cmd, char *args, char **envp)
{
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		ft_cd(args, envp);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		ft_exit();
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		envp = ft_export(envp, args);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		envp = ft_unset(envp, args);
	else
		return (0);
	return (envp);
}
