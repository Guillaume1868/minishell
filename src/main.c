/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/28 15:52:24 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	disp_next_prompt(char **line)
{
	if (g_success == 131)
		write(1, "\033[2K\033[1G", 8);
	free(*line);
	*line = readline ("\033[36;1m$>\033[0m");
}

void	ft_short(int argc, char **argv)
{
	struct termios	attributes;

	(void)argc;
	(void)argv;
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
	int			i;

	ft_short(argc, argv);
	i = 0;
	while (envp[i])
		i++;
	envp = recreate_envp(envp, i, 0);
	if (envp == 0)
		exit(1);
	g_success = 0;
	line = readline ("\033[36;1m$>\033[0m");
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			cmd_lst = parse(line, envp);
			if (((t_cmd *)cmd_lst->content)->args != 0)
				envp = execute_program(0, cmd_lst, envp);
		}
		disp_next_prompt(&line);
	}
	free_envp(envp);
}
