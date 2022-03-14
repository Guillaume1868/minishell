/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:42 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 12:21:02 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pack_p(t_params *p, int *i, char *line, char *quote)
{
	p->i = i;
	p->line = line;
	p->quote = quote;
}

void	pack_p2(t_params *p, t_cmd *cmd, t_list *c)
{
	p->res = cmd;
	p->c = c;
}

void	redir(t_params *p, char *linei, char **envp)
{
	if (*linei == '<' && *(linei + 1) == '<')
		save_redir(*p, delim_in, 1, envp);
	else if (*linei == '<')
		save_redir(*p, in, 1, envp);
	else if (*linei == '>' && *(linei + 1) == '>')
		save_redir(*p, append_out, 0, envp);
	else if (*linei == '>')
		save_redir(*p, out, 0, envp);
}
