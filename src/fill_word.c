/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/10 13:39:21 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_word(char *res, char *line, char **envp, int *i)
{
	int		j;
	char	q;

	j = 0;
	q = '0';
	while (line[*i] != 0 && !(is_seperator(line[*i]) && q == '0'))
	{
		if (quotes(line[*i], &q) && !(q == line[*i]))
		{
			if (line[*i] == '$' && (q == '\"' || q == '0'))
			{
				//printf("i=%d\n", i);
				ft_memcpy(&res[j], get_env_2(&line[*i + 1], envp), ft_strlen(get_env_2(&line[*i + 1], envp)));
				j += ft_strlen(get_env_2(&line[*i + 1], envp));
				*i += ft_strlen_env(&line[*i + 1]);
				//printf("i=%d line[i]=|%s|\n", i, &line[i]);
			}
			else
			{
				res[j] = line[*i];
				j += 1;
			}
		}
		*i = *i + 1;
	}
}

int	quotes(char c, char *quote)
{
	if (*quote == '0' && (c == '\'' || c == '\"'))
		*quote = c;
	else if (*quote != '0' && c == *quote)
	{
		*quote = '0';
		return (0);
	}
	return (1);
}
