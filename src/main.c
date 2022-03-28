/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 11:10:35 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\b\b  ", 1);
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

void	disp_next_prompt(char **line)
{
	free(*line);
	*line = readline ("\033[36;1m$>\033[0m");
}

void	ft_short(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*cmd_lst;
	char		*path;
	int			i;

	ft_short();
	path = NULL;
	i = 0;
	while (envp[i])
		i++;
	envp = recreate_envp(envp, i, 0);
	if (envp == 0)
		exit(1);
	if (argc == 2)
	{
		cmd_lst = parse(argv[1], envp);
		if (((t_cmd *)cmd_lst->content)->args != 0)
			execute_program(path, cmd_lst, envp);
		//ft_cmdfree(cmd_lst);
		free_envp(envp);
		exit (0);
	}
	g_success = 0;
	line = readline ("\033[36;1m$>\033[0m");
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			cmd_lst = parse(line, envp);
			if (((t_cmd *)cmd_lst->content)->args != 0)
				envp = execute_program(path, cmd_lst, envp);
		}
		disp_next_prompt(&line);
	}
	free_envp(envp);
}
