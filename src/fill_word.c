/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 13:34:25 by gaubert          ###   ########.fr       */
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

void	fill_loop_short(t_loop l)
{
	if (quotes(l.line[*l.i], &l.q) && !(l.q == l.line[*l.i]))
	{
		if (l.line[*l.i] == '$' && (l.q == '\"' || l.q == '0')
			&& (ft_isalnum(l.line[*l.i + 1]) || l.line[*l.i + 1] == '_'))
		{
			ft_memcpy(&l.res[l.j], get_env_2(&l.line[*l.i + 1], l.envp),
				ft_strlen(get_env_2(&l.line[*l.i + 1], l.envp)));
			l.j += ft_strlen(get_env_2(&l.line[*l.i + 1], l.envp));
			*l.i += ft_strlen_env(&l.line[*l.i + 1]);
		}
		else if (l.line[*l.i] == '$' && (l.q == '\"' || l.q == '0')
			&& (l.line[*l.i + 1] == '?'))
			fill_return(l.res, &l.j, l.i);
		else
		{
			l.res[l.j] = l.line[*l.i];
			l.j += 1;
		}
	}
	*l.i = *l.i + 1;
}

void	fill_word(char *res, char *line, char **envp, int *i)
{
	t_loop	loop;

	loop.j = 0;
	loop.q = '0';
	loop.i = i;
	loop.line = line;
	loop.res = res;
	loop.envp = envp;
	while (line[*i] != 0 && !(is_seperator(line[*i]) && loop.q == '0'))
		fill_loop_short(loop);
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
