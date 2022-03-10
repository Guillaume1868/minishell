/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/10 13:11:21 by gaubert          ###   ########.fr       */
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
		printf("%s\n", dir);
	else
		perror("pwd() error");
}

void	disp_next_prompt(char **line)
{
	free(*line);
	*line = readline ("$>");
}

void	ft_echo(char *argument)
{
	int	i;

	i = 0;
	if (!(argument[0] == '-' && argument[1] == 'n'))
	{
		while (argument[i] == ' ')
			i++;
		printf("%s\n", &argument[0]);
	}
	else
	{
		i += 2;
		while (argument[i] == ' ')
			i++;
		printf("%s", &argument[i]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*cmd_lst;

	(void)argc;
	(void)argv;
	if (argc == 2)
	{
		cmd_lst = parse(argv[1], envp);
		ft_lstiter(cmd_lst, print_cmd);
		exit (0);
	}
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	line = readline ("$>");
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			cmd_lst = parse(line, envp);
			ft_lstiter(cmd_lst, print_cmd);
		}
		disp_next_prompt(&line);
	}
	//redire a vbotev si jarrive a print le exit
}
