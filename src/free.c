/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:25:15 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/11 14:57:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_action(void *param)
{
	free(param);
}

static void	redir_action(void *param)
{
	t_redir	*red;

	red = param;
	free(red->str);
	free(param);
}

static void	cmd_action(void *param)
{
	t_cmd	*cmd;

	cmd = param;
	ft_lstclear(&cmd->in_redir, redir_action);
	ft_lstclear(&cmd->out_redir, redir_action);
	ft_lstclear(&cmd->args, free_action);
	free(param);
}

void	ft_cmdfree(t_list *cmd_lst)
{
	ft_lstclear(&cmd_lst, cmd_action);
}
