/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:38:11 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 13:47:49 by gaubert          ###   ########.fr       */
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

char	**make_unset(char **envp, char *args, char **res)
{
	int		i;
	int		j;
	char	*tmp;

	j = -1;
	i = -1;
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
	return (res);
}

char	**ft_unset(char **envp, char *args, t_exec *exec)
{
	int		j;
	char	**res;

	j = 0;
	if (args == 0 || args[0] == '=' || args[0] == '\0'
		|| ft_isdigit(args[0]) == 1)
		return (envp);
	while (envp[j])
		j++;
	res = malloc(sizeof(char *) * j + 1);
	if (res == 0)
		ft_exit(envp, exec);
	res = make_unset(envp, args, res);
	free(envp);
	return (res);
}

char	**ft_export2(char **envp, char *args, char *tmp, int j)
{
	int	i;

	i = 0;
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
	return (envp);
}

char	**ft_export(char **envp, char *args)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = 0;
	if (args == 0)
		while (envp[++i])
			printf("declare -x %s\n", envp[i]);
	else if (args[0] == '=' || ft_isdigit(args[0]) == 1)
		printf("minishell: export: `%s': not a valid identifier\n", args);
	else
		envp = ft_export2(envp, args, tmp, j);
	return (envp);
}
