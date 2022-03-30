/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:37:30 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/29 13:28:46 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_redirect(t_list *cmd_lst, t_exec *exec, int i)
{
	exec_stdin(cmd_lst, exec, i);
	exec_stdout(cmd_lst, exec, i);
	if (cmd_lst->next || ((t_cmd *)cmd_lst->content)->out_redir)
		dup2(exec->link[i * 2 + 1], 1);
	if (i != 0)
		dup2(exec->link[(i - 1) * 2], 0);
}

void	child_program(t_list *cmd_lst, t_exec *exec, int i, char **envp)
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
	if (exec->args == 0)
	{
		exec->cmd_lst_tofree = cmd_lst;
		ft_exit(envp, exec);
	}
	exec->tmp = ((t_cmd *)cmd_lst->content)->args;
	j = 0;
	while (exec->tmp)
	{
		exec->args[j] = (char *)exec->tmp->content;
		exec->tmp = exec->tmp->next;
		j++;
	}
	exec->args[j] = 0;
	std_redirect(cmd_lst, exec, i);
}

char	*setup_exec2(t_exec *exec, int i, t_list *cmd_lst, char *path)
{
	char	*tmp;

	tmp = 0;
	exec->tmp = ((t_cmd *)cmd_lst->content)->args;
	if ((t_list *)exec->tmp->next != 0)
		tmp = (char *)((t_list *)exec->tmp->next)->content;
	exec->cmd_lst_tofree = cmd_lst;
	exec->path = path;
	exec->counter = i;
	return (tmp);
}

void	setup_exec(char *path, t_list *cmd_lst, char **envp, t_exec *exec)
{
	exec->path = path;
	exec->last_success = 0;
	count_pipes(exec, cmd_lst);
	exec->pid = malloc(sizeof(int) * (exec->nbr_pipes + 1));
	exec->link = malloc(sizeof(int) * (2 * exec->nbr_pipes));
	if (exec->pid == 0 || exec->link == 0)
	{
		exec->cmd_lst_tofree = cmd_lst;
		ft_exit(envp, exec);
	}
}
