/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:41:27 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/23 10:55:12 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_stdin(t_list *cmd_lst, t_exec *exec, int i)
{
	if (((t_cmd *)cmd_lst->content)->in_redir)
	{
		exec->tmp = ((t_cmd *)cmd_lst->content)->in_redir;
		if (((t_redir *)exec->tmp->content)->type == 2)
		{
			close(exec->link[(i - 1) * 2]);
			exec->link[(i - 1) * 2] = open(((t_redir *)exec->tmp->content)->str,
					O_RDONLY);
		}
		else if (((t_redir *)exec->tmp->content)->type == 3)
		{
			ft_heredoc(exec->tmp, exec, i);
			if (exec->nbr_pipes == 0)
				exec->nbr_pipes++;
		}
	}
}

void	exec_stdout(t_list *cmd_lst, t_exec *exec, int i)
{
	if (((t_cmd *)cmd_lst->content)->out_redir)
	{
		exec->tmp = ((t_cmd *)cmd_lst->content)->out_redir;
		close(exec->link[i * 2 + 1]);
		if (((t_redir *)exec->tmp->content)->type == 0)
			exec->link[i * 2 + 1] = open(((t_redir *)exec->tmp->content)->str,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (((t_redir *)exec->tmp->content)->type == 1)
			exec->link[i * 2 + 1] = open(((t_redir *)exec->tmp->content)->str,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

void	count_pipes(t_exec *exec, t_list *cmd_lst)
{
	exec->nbr_pipes = -1;
	exec->tmp = cmd_lst;
	while (exec->tmp)
	{
		exec->nbr_pipes++;
		exec->tmp = exec->tmp->next;
	}
}

void	change_pip(int *pip, int i, t_exec *exec)
{
	close(pip[1]);
	if (i == 0)
	{
		close(exec->link[0]);
		exec->link[0] = pip[0];
		dup2(exec->link[0], 0);
	}
	else
	{
		close(exec->link[(i - 1) * 2]);
		exec->link[(i - 1) * 2] = pip[0];
	}
}

void	ft_heredoc(t_list *tmp, t_exec *exec, int i)
{
	char	*line;
	int		pip[2];

	pipe(pip);
	line = readline(">");
	while (1)
	{
		if (signal(SIGQUIT, exit) == SIG_ERR)
			printf("failed to register interrupts with kernel\n");
		if (line[0] != '\0')
		{
			if (ft_strncmp(((t_redir *)tmp->content)->str, line,
					ft_strlen(((t_redir *)tmp->content)->str) + 1) == 0)
				break ;
			ft_putendl_fd(line, pip[1]);
		}
		free(line);
		line = readline(">");
	}
	free(line);
	change_pip(pip, i, exec);
}
