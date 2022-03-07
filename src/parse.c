/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:42 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 14:33:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(char *str, int *i)
{
	while (str[*i] == ' ')
		*i = *i + 1;
}

void	save_redir(t_params p, enum e_type type, int in_mode)
{
	t_redir	*tmp;

	if (type == append_out || type == delim_in)
		*p.i = *p.i + 2;
	else
		*p.i = *p.i + 1;
	skip_space(p.line, p.i);
	tmp = malloc(sizeof(t_redir));
	tmp->str = get_word(p.line, p.i, p.quote);
	tmp->type = type;
	if (in_mode)
		ft_lstadd_back(&p.res->in_redir, ft_lstnew(tmp));
	else
		ft_lstadd_back(&p.res->out_redir, ft_lstnew(tmp));
}

void	save_command(t_params *p, t_cmd *cmd, int pipe, t_list *c)
{
	*p->i = *p->i + 1;
	cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	cmd->pipe_from_prec = pipe;
	ft_lstadd_back(&c, ft_lstnew(cmd));
	p->res = cmd;
}

//TODO:Error on >> to nothing
t_list	*parse(char *line, char **envp)
{
	t_list		*c;
	t_cmd		*cmd;
	int			i;
	char		quote;
	t_params	p;

	(void)envp;
	quote = '0';
	i = 0;
	cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	ft_lstadd_back(&c, ft_lstnew(cmd));
	p.i = &i;
	p.line = line;
	p.quote = &quote;
	p.res = cmd;
	while (line[i])
	{
		quotes(line[i], &quote);
		if (quote == '0' && line[i] == ';')
			save_command(&p, cmd, 0, c);
		else if (quote == '0' && line[i] == '|')
			save_command(&p, cmd, 1, c);
		else if (quote == '0' && (line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '<' && line[i + 1] == '<')
				save_redir(p, delim_in, 1);
			else if (line[i] == '<')
				save_redir(p, in, 1);
			else if (line[i] == '>' && line[i + 1] == '>')
				save_redir(p, append_out, 0);
			else if (line[i] == '>')
				save_redir(p, out, 0);
		}
		else if (line[i] != ' ')
		{
			if (p.res->name == NULL)
				p.res->name = get_word(line, &i, &quote);
			else
				ft_lstadd_back(&p.res->args, ft_lstnew(get_word(line, &i, &quote)));
		}
		else
			i++;
	}
	return (c);
}
