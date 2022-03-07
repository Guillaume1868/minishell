/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:59:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 13:59:10 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	if (c == ' ' | c == '<' | c == '>' | c == ';' | c == '|')
		return (1);
	return (0);
}

char	*get_word(char *line, int *i, char *quote)
{
	char	*start;
	char	*end;
	char	*res;

	start = &line[*i];
	while (line[*i] != 0 && !(is_seperator(line[*i]) && *quote == '0'))
	{
		*i = *i + 1;
		quotes(line[*i], quote);
	}
	end = &line[*i - 1];
	res = malloc_word(start, end);
	return (res);
}

char	*malloc_word(char *start, char *end)
{
	char	quote;
	int		i;
	char	*res;
	int		count;

	quote = '0';
	i = -1;
	count = 0;
	while (start + ++i <= end)
	{
		quotes(*(start + i), &quote);
		if (*(start + i) != quote)
			count++;
	}
	res = ft_calloc(sizeof(char), count + 1);
	i = -1;
	count = -1;
	quote = '0';
	while (start + ++i <= end)
	{
		if (quotes(*(start + i), &quote) && *(start + i) != quote)
			res[++count] = start[i];
	}
	return (res);
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
