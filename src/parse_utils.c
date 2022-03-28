/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:59:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 11:29:32 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	if (c == ' ' | c == '<' | c == '>' | c == ';' | c == '|')
		return (1);
	return (0);
}

void	env_cnt_short(int *del, int *add)
{
	char	*tmp;

	tmp = ft_itoa(g_success);
	*del += 2;
	*add += ft_strlen(tmp) + 1;
	free(tmp);
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
			if (line[i] == '$' && (q == '\"' || q == '0')
				&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
			{
				*del += ft_strlen_env(&line[i + 1]) + 1;
				*add += ft_strlen(get_env_2(&line[i + 1], envp));
			}
			else if (line[i] == '$' && (q == '\"' || q == '0')
				&& line[i + 1] == '?')
			{
				env_cnt_short(del, add);
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
