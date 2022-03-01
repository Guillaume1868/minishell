/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/01 12:43:59 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\b\b  ", 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	pwd(void)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		printf("Current working dir: %s\n", dir);
	}
	else
	{
		perror("pwd() error");
	}
}

void	disp_next_prompt(char **line)
{
	free(*line);
	*line = readline ("$>");
}

int	main(void)
{
	char	*line;

	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	line = readline ("$>");
	while (line != NULL)
	{
		add_history(line);
		printf("%s\n", line);
		if (ft_strncmp("exit", line, 5) == 0)
			exit(0);
		if (ft_strncmp("$", line, 1) == 0)
			env(line + 1);
		if (ft_strncmp("pwd", line, 4) == 0)
			pwd();
		disp_next_prompt(&line);
	}
}
