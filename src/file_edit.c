/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:41:27 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/08 11:02:23 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_into_file(char *args, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
		return (0);
	write(fd, args, ft_strlen(args));
	close(fd);
	return (1);
}

char	*read_file(char *args, char *file)
{
	int		fd;
	char	*result;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	result = 0;
	tmp = 1;
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
}

int	execute_program(t_list *args, char **envp)
{
	char	**result;
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = args;
	while (tmp)
	{
		j++;
		tmp->next;
	}
	result = malloc(sizeof(char *) * (j + 1));
	while (args)
	{
		result[i] = ft_strdup((char *)args->content);
		args = args->next;
		i++;
	}
	result[i] = 0;
	execve("./", args, envp);
}
