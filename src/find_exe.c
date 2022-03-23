/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:41:07 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 10:20:53 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file(const char *name)
{
	DIR	*directory;

	directory = opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
	if (errno == ENOTDIR)
	{
		return (1);
	}
	return (-1);
}

static char	*build_path(char *path, char *name)
{
	char	*res;
	int		path_size;
	int		name_size;

	if (ft_strncmp(name, ".", 2) == 0 || ft_strncmp(name, "..", 3) == 0)
		return (NULL);
	path_size = ft_strlen(path);
	name_size = ft_strlen(name);
	res = malloc(path_size + name_size + 2);  // TODO: protect return null
	if (!res)
		return (NULL);
	ft_memcpy(res, path, path_size);
	res[path_size] = '/';
	ft_memcpy(&res[path_size + 1], name, name_size);
	res[path_size + name_size + 1] = 0;
	return (res);
}

static int	f_sh(char *f_path, struct dirent *ep, char *name, DIR *dp)
{
	if (!access(f_path, X_OK) && is_file(f_path))
	{
		if (!ft_strncmp(ep->d_name, name, ft_strlen(name) + 1))
		{
			closedir(dp);
			return (1);
		}
	}
	return (0);
}

static char	*find_executable(char *name, char *path)
{
	DIR				*dp;
	struct dirent	*ep;
	char			*f_path;

	dp = opendir (path);
	if (dp != NULL)
	{
		ep = readdir(dp);
		while (ep)
		{
			f_path = build_path(path, ep->d_name);
			if (f_path)
			{
				if (f_sh(f_path, ep, name, dp))
					return (f_path);
			}
			ep = readdir(dp);
			free (f_path);
		}
	}
	closedir(dp);
	return (NULL);
}

char	*get_executable_path(char *name, char **envp)
{
	int		i;
	char	**path;
	char	*ret;

	i = -1;
	path = ft_split(get_env("PATH", envp), ':');
	while (path[++i])
	{
		ret = find_executable(name, path[i]);
		free(path[i]);
		if (ret)
			return (ret);
	}
	free(path);
	return (NULL);
}
