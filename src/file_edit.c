/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:41:27 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 14:32:08 by gaubert          ###   ########.fr       */
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

int	execute_program(char *path, t_list *cmd_lst, char **envp)
{
	t_list	*tmp;
	t_list	*args_list;
	char	**args;
	int		i;
	int		j;
	int		nbr_pipes;
	pid_t	*pid;
	int		*link;

	nbr_pipes = -1;
	tmp = cmd_lst;
	while (tmp)
	{
		nbr_pipes++;
		tmp = tmp->next;
	}
	i = -1;
	pid = malloc(sizeof(int) * (nbr_pipes + 1));
	link = malloc(sizeof(int) * (2 * nbr_pipes));
	while (++i < nbr_pipes)
		if (pipe(link + i * 2) < 0)
			exit(1);
	i = 0;
	while (cmd_lst)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			args_list = ((t_cmd *)cmd_lst->content)->args;
			path = get_executable_path((char *)args_list->content, envp);
			tmp = args_list;
			j = 0;
			while (tmp)
			{
				tmp = tmp->next;
				j++;
			}
			args = malloc(sizeof(char *) * (j + 1));
			tmp = args_list;
			j = 0;
			while (tmp)
			{
				args[j] = (char *)tmp->content;
				tmp = tmp->next;
				j++;
			}
			args[j] = 0;
			print_cmd(cmd_lst->content);
			if (((t_cmd *)cmd_lst->content)->out_redir)
			{
				tmp = ((t_cmd *)cmd_lst->content)->out_redir;
				if (((t_redir *)tmp->content)->type == 0)
				{
					close(link[i * 2 + 1]);
					link[i * 2 + 1] = open(((t_redir *)tmp->content)->str,
							O_WRONLY | O_CREAT);
				}
				else if (((t_redir *)tmp->content)->type == 1)
				{
					close(link[i * 2 + 1]);
					printf("WTFDSFsGFDSGDSFG");
					link[i * 2 + 1] = open(((t_redir *)tmp->content)->str,
							O_WRONLY | O_APPEND | O_CREAT);
					/*while (j != 0 && j != -1)
						j = read(link[i * 2 + 1], 0, 1);*/
				}
			}
			else if (((t_cmd *)cmd_lst->content)->in_redir)
			{
				tmp = ((t_cmd *)cmd_lst->content)->in_redir;
				if (((t_redir *)tmp->content)->type == 2)
				{
					close(link[(i - 1) * 2]);
				}
				else if (((t_redir *)tmp->content)->type == 3)
				{
					close(link[(i - 1) * 2]);
					link[(i - 1) * 2] = open(((t_redir *)tmp->content)->str,
							O_WRONLY);
				}
			}
			if (cmd_lst->next || ((t_cmd *)cmd_lst->content)->out_redir)
				dup2(link[i * 2 + 1], 1);
			if (i != 0 || ((t_cmd *)cmd_lst->content)->in_redir)
				dup2(link[(i - 1) * 2], 0);
			j = -1;
			while (++j < (2 * (nbr_pipes)))
				close(link[j]);
			if (path)
				execve(path, args, envp);
			free(args);
			free(path);
			exit(1);
		}
		i++;
		cmd_lst = cmd_lst->next;
	}
	i = -1;
	while (++i < (2 * nbr_pipes))
		close(link[i]);
	i = -1;
	while (++i < nbr_pipes + 1)
		waitpid(pid[i], 0, 0);
	free(link);
	free(pid);
	return (1);
}
