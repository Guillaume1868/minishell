/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:37:30 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 10:39:23 by gaubert          ###   ########.fr       */
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
	exec->tmp = ((t_cmd *)cmd_lst->content)->args;
	if (exec->args == 0 || exec->tmp == 0)
	{
		exec->cmd_lst_tofree = &cmd_lst;
		ft_exit(envp, exec);
	}
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
