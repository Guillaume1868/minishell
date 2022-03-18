/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:41:27 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/18 10:40:40 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_into_file(char *args, char *file)
{
	int	fd;

	fd = open(file, O_CREAT);
	if (fd == -1)
		return (0);
	write(fd, args, ft_strlen(args));
	close(fd);
	return (1);
}

/*char	*read_file(char *args, char *file)
{
	int		fd;
	char	*result;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	result = 0;
	tmp = "2";
	while (tmp)
	{
		tmp = ft_strdup(get_next_line(fd));
		if (tmp)
		{
			result = ft_strjoin(result, tmp);
			free(tmp);
		}
	}
	close(fd);
	return (result);
}*/

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
			ft_heredoc(exec->tmp, exec->link, i);
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

void	itering_prog(char *path, t_list *cmd_lst, t_exec *exec, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_lst)
	{
		exec->pid[i] = fork();
		if (exec->pid[i] == 0)
		{
			exec->tmp = ((t_cmd *)cmd_lst->content)->args;
			path = get_executable_path((char *)exec->tmp->content, envp);
			child_program(cmd_lst, exec, i);
			j = -1;
			while (++j < (2 * (exec->nbr_pipes)))
				close(exec->link[j]);
			if (path)
				execve(path, exec->args, envp);
			free(exec->args);
			free(path);
			exit(1);
		}
		i++;
		cmd_lst = cmd_lst->next;
	}
}

void	execute_program(char *path, t_list *cmd_lst, char **envp)
{
	t_exec	exec;
	int		i;

	exec.nbr_pipes = -1;
	exec.tmp = cmd_lst;
	while (exec.tmp)
	{
		exec.nbr_pipes++;
		exec.tmp = exec.tmp->next;
	}
	exec.pid = malloc(sizeof(int) * (exec.nbr_pipes + 1));
	exec.link = malloc(sizeof(int) * (2 * exec.nbr_pipes));
	i = -1;
	while (++i < exec.nbr_pipes)
		if (pipe(exec.link + i * 2) < 0)
			exit(1);
	itering_prog(path, cmd_lst, &exec, envp);
	i = -1;
	while (++i < (2 * exec.nbr_pipes))
		close(exec.link[i]);
	i = -1;
	while (++i < exec.nbr_pipes + 1)
		waitpid(exec.pid[i], 0, 0);
	free(exec.link);
	free(exec.pid);
}

void	change_pip(int *pip, int i, int *link)
{
	close(pip[1]);
	if (i == 0)
	{
		close(link[0]);
		link[0] = pip[0];
		dup2(link[0], 0);
	}
	else
	{
		close(link[(i - 1) * 2]);
		link[(i - 1) * 2] = pip[0];
	}
}

void	ft_heredoc(t_list *tmp, int *link, int i)
{
	char	*line;
	int		pip[2];

	pipe(pip);
	line = readline("heredoc>");
	while (1)
	{
		if (line[0] != '\0')
		{
			if (ft_strncmp(line, ((t_redir *)tmp->content)->str,
					ft_strlen(line)) == 0 && ft_strlen(line) != 0)
				break ;
			ft_putendl_fd(line, pip[1]);
		}
		free(line);
		line = readline("heredoc>");
	}
	free(line);
	change_pip(pip, i, link);
}
