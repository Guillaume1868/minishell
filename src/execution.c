/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:53:56 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 11:56:34 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int static	g_success = 1;

void	child_program(t_list *cmd_lst, t_exec *exec, int i)
{
	int		j;

	exec->tmp = ((t_cmd *)cmd_lst->content)->args;
	j = 0;
	while (exec->tmp)
	{
		exec->tmp = exec->tmp->next;
		j++;
	}
	exec->args = malloc(sizeof(char *) * (j + 1));
	exec->tmp = ((t_cmd *)cmd_lst->content)->args;
	j = 0;
	while (exec->tmp)
	{
		exec->args[j] = (char *)exec->tmp->content;
		exec->tmp = exec->tmp->next;
		j++;
	}
	exec->args[j] = 0;
	exec_stdin(cmd_lst, exec, i);
	exec_stdout(cmd_lst, exec, i);
	if (cmd_lst->next || ((t_cmd *)cmd_lst->content)->out_redir)
		dup2(exec->link[i * 2 + 1], 1);
	if (i != 0)
		dup2(exec->link[(i - 1) * 2], 0);
}

void	pid_equal_zero(t_list *cmd_lst, t_exec *exec, char	**envp, char *tmp)
{
	int		j;
	char	**envptmp;

	exec->pid[exec->counter] = fork();
	if (exec->pid[exec->counter] == 0)
	{
		exec->tmp = ((t_cmd *)cmd_lst->content)->args;
		exec->path = get_executable_path((char *)exec->tmp->content, envp);
		child_program(cmd_lst, exec, exec->counter);
		if (exec->path == 0 && exec->args[0][0] == '/')
		{
			exec->path = ft_strdup(exec->args[0]);
			free(exec->args[0]);
			exec->args[0] = ft_strdup(ft_strrchr(exec->path, '/'));
		}
		print_cmd(cmd_lst->content);
		j = -1;
		while (++j < (2 * (exec->nbr_pipes)))
			close(exec->link[j]);
		if (check_builtin_forked(exec->args[0], exec->args, envp) == 0)
		{
			exec->tmp = ((t_cmd *)cmd_lst->content)->args;
			envptmp = check_builtin((char *)exec->tmp->content, tmp, envp);
			if (exec->path && envptmp == 0)
			{
				g_success = 0;
				execve(exec->path, exec->args, envp);
			}
			else if (exec->path == 0)
			{
				g_success = 1;
				printf("minishell: %s: command not found\n", exec->args[0]);
			}
			else if (envptmp != 0)
				g_success = 0;
		}
		else
			g_success = 0;
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
	char	**envptmp;

	i = 0;
	while (cmd_lst)
	{
		envptmp = 0;
		tmp = 0;
		exec->tmp = ((t_cmd *)cmd_lst->content)->args;
		if ((t_list *)exec->tmp->next != 0)
			tmp = (char *)((t_list *)exec->tmp->next)->content;
		if (exec->nbr_pipes == 0)
			envptmp = check_builtin((char *)exec->tmp->content, tmp, envp);
		exec->counter = i;
		exec->path = path;
		if (envptmp == 0)
			pid_equal_zero(cmd_lst, exec, envp, tmp);
		else
		{
			envp = envptmp;
			g_success = 0;
		}
		i++;
		cmd_lst = cmd_lst->next;
	}
	return (envp);
}

char	**execute_program(char *path, t_list *cmd_lst, char **envp)
{
	t_exec	exec;
	int		i;

	g_success = 1;
	count_pipes(&exec, cmd_lst);
	exec.pid = malloc(sizeof(int) * (exec.nbr_pipes + 1));
	exec.link = malloc(sizeof(int) * (2 * exec.nbr_pipes));
	i = -1;
	while (++i < exec.nbr_pipes)
		if (pipe(exec.link + i * 2) < 0)
			exit(1);
	envp = itering_prog(path, cmd_lst, &exec, envp);
	i = -1;
	while (++i < (2 * exec.nbr_pipes))
		close(exec.link[i]);
	i = -1;
	while (++i < exec.nbr_pipes + 1)
		waitpid(exec.pid[i], 0, 0);
	free(exec.link);
	free(exec.pid);
	printf("Success: %d\n", g_success);
	return (envp);
}
