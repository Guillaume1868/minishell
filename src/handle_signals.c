/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:52:36 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 15:56:20 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals2(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		g_success = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_success = 128 + signo;
	}
}

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_success = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_success = 128 + signo;
	}
}