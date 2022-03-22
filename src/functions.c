/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:38:11 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/21 16:00:07 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (0);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(&res[ft_strlen(s1)], s2, ft_strlen(s2));
	ft_memcpy(&res[ft_strlen(s1) + ft_strlen(s2)], "\0", 1);
	free(s1);
	return (res);
}

char	**ft_unset(char **envp, char *args)
{
	int		i;
	int		j;
	char	*tmp;
	char	**res;

	i = -1;
	j = 0;
	if (args == 0 || args[0] == '=' || args[0] == '\0'
		|| ft_isdigit(args[0]) == 1)
		return (envp);
	while (envp[j])
		j++;
	res = malloc(sizeof(char *) * j + 1);
	j = -1;
	while (envp[++i])
	{
		tmp = ft_strchr(envp[i], '=');
		if (ft_strncmp(envp[i], args, ft_strlen(envp[i]) - ft_strlen(tmp)) == 0)
		{
			free(envp[i]);
			i++;
		}
		if (envp[i])
			res[++j] = ft_strdup(envp[i]);
		free(envp[i]);
	}
	res[++j] = 0;
	res[++j] = 0;
	free(envp);
	return (res);
}

char	**ft_export(char **envp, char *args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (args == 0 || args[0] == '=' || args[0] == '\0'
		|| ft_isdigit(args[0]) == 1)
		printf("minishell: export: `%s': not a valid identifier\n", args);
	else
	{
		while (args[j] != ' ' && args[j] != '\0')
			j++;
		tmp = ft_strchr(args, '=');
		if (tmp != 0)
		{
			tmp++;
			while (envp[i] && ft_strncmp(envp[i], args,
					ft_strlen(args) - ft_strlen(tmp)) != 0)
				i++;
			envp = make_export(envp, args, tmp, i);
		}
	}
	return (envp);
}

char	**recreate_envp(char **envp, int len, int ismalloc)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (envp[++i])
	{
		res[i] = ft_strdup(envp[i]);
		if (ismalloc == 1)
			free(envp[i]);
	}
	res[i] = 0;
	res[i + 1] = 0;
	if (ismalloc == 1)
		free(envp);
	return (res);
}

char	**make_export(char **envp, char *args, char *tmp, int i)
{
	int	j;

	j = 0;
	if (envp[i])
	{
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		tmp = ft_substr(envp[i], 0, j);
		j = 0;
		while (args[j] && args[j] != '=')
			j++;
		envp[i] = ft_strjoinfree(tmp, &args[j]);
	}
	else
	{
		i = 0;
		while (envp[i])
			i++;
		i++;
		envp = recreate_envp(envp, i, 1);
		if (tmp)
			envp[i - 1] = ft_strdup(args);
	}
	return (envp);
}
