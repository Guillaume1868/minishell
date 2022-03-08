/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:09:03 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/08 11:16:03 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(void *arg)
{
	printf("- %s\n", (char *)arg);
}

void	print_redir(void *arg)
{
	t_redir	*tmp;

	tmp = arg;
	printf("|%s| type=%d\n", tmp->str, tmp->type);
}

void	print_cmd(void *param)
{
	t_cmd	*cmd;

	cmd = param;
	if (cmd->pipe_from_prec)
		printf("==========\n%sPIPED command:%s\n", KRED, KNRM);
	else
		printf("==========\n%scommand:%s\n", KYEL, KNRM);
	if (cmd->args)
		printf("args:\n");
	ft_lstiter(cmd->args, print_lst);
	if (cmd->in_redir)
		printf("in redirs:\n");
	ft_lstiter(cmd->in_redir, print_redir);
	if (cmd->out_redir)
		printf("out redirs:\n");
	ft_lstiter(cmd->out_redir, print_redir);
	printf("==========\n");
}
