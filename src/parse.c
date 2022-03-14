/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:42 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 12:45:31 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(char *str, int *i)
{
	while (str[*i] == ' ')
		*i = *i + 1;
}

int	save_redir2(t_params p, int in_mode, t_redir *tmp)
{
	t_list	*lst;

	lst = ft_lstnew(tmp);
	if (!lst)
		return (f_free(tmp->str) + f_free(tmp) + ft_cmdfree(p.c) + f_exit(1));
	if (in_mode)
		ft_lstadd_back(&p.cmd->in_redir, lst);
	else
		ft_lstadd_back(&p.cmd->out_redir, lst);
	return (0);
}

int	save_redir(t_params p, enum e_type type, int in_mode, char **envp)
{
	t_redir	*tmp;

	if (type == append_out || type == delim_in)
		*p.i = *p.i + 2;
	else
		*p.i = *p.i + 1;
	skip_space(p.line, p.i);
	tmp = malloc(sizeof(t_redir));
	if (!tmp)
		return (ft_cmdfree(p.c) + f_free(tmp) + f_exit(1));
	tmp->str = get_word(p.line, p.i, p.quote, envp);
	if (!tmp->str)
		return (ft_cmdfree(p.c) + f_free(tmp) + f_free(tmp->str) + f_exit(1));
	tmp->type = type;
	if (*tmp->str == 0)
	{
		printf("redirect to nothing\n");
		return (ft_cmdfree(p.c) + f_free(tmp) + f_free(tmp->str) + f_exit(1));
	}
	save_redir2(p, in_mode, tmp);
	return (1);
}

int	save_command(t_params *p, int pipe)
{
	t_list	*tmp;

	*p->i = *p->i + 1;
	p->cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	if (!p->cmd)
		return (ft_cmdfree(p->c) + f_exit(1));
	p->cmd->pipe_from_prec = pipe;
	tmp = ft_lstnew(p->cmd);
	if (!tmp)
		return (f_free(p->cmd) + ft_cmdfree(p->c) + f_exit(1));
	ft_lstadd_back(&p->c, tmp);
	return (0);
}

t_list	*parse(char *line, char **envp)
{
	int			i;
	char		quote;
	t_params	p;

	quote = '0';
	i = 0;
	p.c = NULL;
	p.cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	if (!p.cmd)
		exit(1);
	ft_lstadd_back(&p.c, ft_lstnew(p.cmd));//TODO:protecc
	pack_p(&p, &i, line, &quote);
	while (line[i])
	{
		quotes(line[i], &quote);
		if (quote == '0' && line[i] == ';')
			save_command(&p, 0);
		else if (quote == '0' && line[i] == '|')
			save_command(&p, 1);
		else if (quote == '0' && (line[i] == '<' || line[i] == '>'))
			redir(&p, &line[i], envp);
		else if (line[i] != ' ')
			ft_lstadd_back(&p.cmd->args, ft_lstnew(get_word(line, &i, &quote, envp)));  // TODO: protect return null // TODO: protect return null
		else
			i++;
	}
	return (p.c);
}
