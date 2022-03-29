/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:53:56 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/29 13:54:10 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_equal_zero2(t_list *cmd_lst, t_exec *exec, char	**envp, char *tmp)
{
	int		j;
	char	**envptmp;

	envptmp = 0;
	j = -1;
	while (++j < (2 * (exec->nbr_pipes)))
		close(exec->link[j]);
	if (check_builtin_forked(exec->args[0], exec->args, envp) == 0)
	{
		exec->tmp = ((t_cmd *)cmd_lst->content)->args;
		envptmp = check_builtin((char *)exec->tmp->content, tmp, envp, exec);
		if (exec->path && envptmp == 0)
			execve(exec->path, exec->args, envp);
		else if (exec->path == 0)
			printf("minishell: %s: command not found\n", exec->args[0]);
	}
}

void	pid_equal_zero(t_list *cmd_lst, t_exec *exec, char	**envp, char *tmp)
{
	int		j;

	exec->pid[exec->counter] = fork();
	if (exec->pid[exec->counter] == 0)
	{
		exec->tmp = ((t_cmd *)cmd_lst->content)->args;
		exec->path = get_executable_path((char *)exec->tmp->content, envp);
		child_program(cmd_lst, exec, exec->counter, envp);
		if (exec->path == 0 && exec->args[0][0] == '/')
		{
			exec->path = ft_strdup(exec->args[0]);
			free(exec->args[0]);
			exec->args[0] = ft_strdup(ft_strrchr(exec->path, '/'));
		}
		else if (exec->args[0][0] == '.' && exec->args[0][1] == '/')
			exec->path = ft_strdup(exec->args[0]);
		pid_equal_zero2(cmd_lst, exec, envp, tmp);
		j = -1;
		while (exec->args[++j])
			free(exec->args[j]);
		free(exec->args);
		free(exec->path);
		exit(1);
	}
}

/*char	*join_args(t_list *args)
{
	char	*res;

	res = (char *)args->content;
	if (args->next)
		res = ft_strjoinfree(res, " ");
	args = args->next;
	while (args)
	{
		res = ft_strjoinfree(res, (char *)args->content);
		if (args->next)
			res = ft_strjoinfree(res, " ");
		free(args->content);
		args = args->next;
	}
	return (res);
}*/
/*
to put bellow after exec->tmp = ((t_cmd *)cmd_lst->content)->args;
if (((t_cmd *)cmd_lst->content)->args->next)
			((t_cmd *)cmd_lst->content)->args->next->content =
			join_args(exec->tmp->next);*/

char	**itering_prog(char *path, t_list *cmd_lst, t_exec *exec, char **envp)
{
	int		i;
	char	*tmp;
	char	**envtmp;

	i = 0;
	envtmp = 0;
	while (cmd_lst)
	{
		if (((t_cmd *)cmd_lst->content)->args == 0)
		{
			g_success = 1;
			printf("minishell: pipe error\n");
			return (envp);
		}
		tmp = setup_exec2(exec, i, cmd_lst, path);
		if (exec->nbr_pipes == 0)
			envtmp = check_builtin((char *)exec->tmp->content, tmp, envp, exec);
		if (envtmp == 0)
			pid_equal_zero(cmd_lst, exec, envp, tmp);
		else
			envp = envtmp;
		i++;
		cmd_lst = cmd_lst->next;
	}
	return (envp);
}

void	wait_close_forks(t_exec *exec)
{
	int		i;
	int		status;

	i = -1;
	while (++i < (2 * exec->nbr_pipes))
		close(exec->link[i]);
	i = -1;
	while (++i < exec->nbr_pipes + 1)
		waitpid(exec->pid[i], &status, 0);
	if (g_success == 2)
		g_success = 0;
	else if (g_success == 3)
		g_success = 1;
	else if (WIFEXITED(status))
		g_success = WEXITSTATUS(status);
	free(exec->link);
	free(exec->pid);
}

char	**execute_program(char *path, t_list *cmd_lst, char **envp)
{
	t_exec	exec;
	int		i;

	if (signal(SIGINT, handle_signals2) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals2) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	i = -1;
	setup_exec(path, cmd_lst, envp, &exec);
	while (++i < exec.nbr_pipes)
		if (pipe(exec.link + i * 2) < 0)
			exit(1);
	envp = itering_prog(path, cmd_lst, &exec, envp);
	wait_close_forks(&exec);
	ft_cmdfree(cmd_lst);
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	return (envp);
}
