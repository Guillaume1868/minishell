/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:01:53 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/29 11:19:33 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *args, char **envp)
{
	char	*tmp;
	int		i;

	i = 0;
	g_success = 2;
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
		{
			g_success = 1;
			printf("cd: %s: No such file or directory\n", args);
		}
		free(tmp);
	}
	return (1);
}

void	ft_help(void)
{
	printf("HELP OF MINISHELL\nThe following are built in: cd help exit\n"
		"Use the man command for information on other programs.\n");
	g_success = 2;
}

int	ft_exit(char **envp, t_exec *exec)
{
	int	i;

	i = -1;
	ft_putstr_fd("exit\n", 1);
	free_envp(envp);
	if (*exec->cmd_lst_tofree)
		ft_cmdfree(*exec->cmd_lst_tofree);
	if (exec->link)
		free(exec->link);
	if (exec->pid)
		free(exec->pid);
	if (exec->path)
		free(exec->path);
	g_success = 2;
	exit(1);
	return (0);
}

void	ft_env(char	**envp)
{
	int	i;

	g_success = 2;
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
