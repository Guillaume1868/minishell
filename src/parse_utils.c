/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:59:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 10:25:10 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	if (c == ' ' | c == '<' | c == '>' | c == ';' | c == '|')
		return (1);
	return (0);
}

void	env_cnt(char *line, int *add, int *del, char **envp)
{
	int		i;
	char	q;

	i = 0;
	q = '0';
	while (line[i] != 0 && !(is_seperator(line[i]) && q == '0'))
	{
		if (quotes(line[i], &q) && !(q == line[i]))
		{
			if (line[i] == '$' && (q == '\"' || q == '0'))
			{
				*del += ft_strlen_env(&line[i + 1]) + 1;
				*add += ft_strlen(get_env_2(&line[i + 1], envp));
			}
		}
		i = i + 1;
	}
}

int	char_cnt(char *line)
{
	int		i;
	int		cnt;
	char	q;

	i = 0;
	cnt = 0;
	q = '0';
	while (line[i] != 0 && !(is_seperator(line[i]) && q == '0'))
	{
		if (quotes(line[i], &q) && !(q == line[i]))
			cnt++;
		i = i + 1;
	}
	return (cnt);
}

char	*calloc_word(char *line, char **envp)
{
	int		add;
	int		del;
	int		count;

	add = 0;
	del = 0;
	env_cnt(line, &add, &del, envp);
	count = char_cnt(line);
	return (ft_calloc(sizeof(char), count + add - del + 1));
}

char	*get_word(char *line, int *i, char *quote, char **envp)
{
	char	*res;

	(void) quote;
	res = calloc_word(&line[*i], envp);
	if (!res)
		return (NULL);
	fill_word(res, line, envp, i);
	*quote = '0';
	return (res);
}
