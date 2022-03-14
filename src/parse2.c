/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:42 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 13:05:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pack_p(t_params *p, int *i, char *line, char *quote)
{
	p->i = i;
	p->line = line;
	p->quote = quote;
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

void	add_cmd(t_params *p)
{
	t_list	*tmp;

	p->c = NULL;
	p->cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	if (!p->cmd)
		exit(1);
	tmp = ft_lstnew(p->cmd);
	if (!tmp)
	{
		free(p->cmd);
		f_exit(1);
	}
	ft_lstadd_back(&p->c, tmp);
}

void	add_word(t_params *p, char **envp)
{
	char		*ctmp;
	t_list		*ltmp;

	ctmp = get_word(p->line, p->i, p->quote, envp);
	if (!ctmp)
	{
		ft_cmdfree(p->c);
		exit(1);
	}
	ltmp = ft_lstnew(ctmp);
	if (!ltmp)
	{
		free(ctmp);
		ft_cmdfree(p->c);
		exit(1);
	}
	ft_lstadd_back(&p->cmd->args, ltmp);
}
