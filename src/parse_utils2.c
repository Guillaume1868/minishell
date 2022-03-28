/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:25:05 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 11:25:30 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
