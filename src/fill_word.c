/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 13:52:43 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_return(char *res, int *j, int *i)
{
	char	*tmp;

	tmp = ft_itoa(g_success);
	ft_memcpy(&res[*j], tmp, ft_strlen(tmp));
	*i += 1;
	*j += ft_strlen(tmp);
	free(tmp);
}

void	fill_word_shortener(int *j, int *i, char *line, char *res)
{
	res[*j] = line[*i];
	*j += 1;
}

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
			if (line[*i] == '$' && (q == '\"' || q == '0')
				&& (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
			{
				ft_memcpy(&res[j], get_env_2(&line[*i + 1], envp),
					ft_strlen(get_env_2(&line[*i + 1], envp)));
				j += ft_strlen(get_env_2(&line[*i + 1], envp));
				*i += ft_strlen_env(&line[*i + 1]);
			}
			else if (line[*i] == '$' && (q == '\"' || q == '0')
				&& (line[*i + 1] == '?'))
				fill_return(res, &j, i);
			else
				fill_word_shortener(&j, i, line, res);
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
