/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/01 15:37:52 by gaubert          ###   ########.fr       */
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

void	check_prompt(char *line, char **envp)
{
	int		i;
	char	*argument;

	i = 0;
	argument = line;
	if (line[0] != '\0')
	{
		while (line[i] != ' ' && line[i] != '\0')
			i++;
		argument = ft_strchr(line, ' ');
		if (argument != 0)
			argument++;
		if (ft_strncmp(line, "cd", i) == 0)
			ft_cd(argument, envp);
		else if (ft_strncmp(line, "exit", i) == 0)
			ft_exit();
		else if (ft_strncmp(line, "help", i) == 0)
			ft_help();
		else if (line[0] != '\0')
			printf("minishell: %s command not found\n", line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	line = readline ("$>");
	while (line != NULL)
	{
		if (line[0] != '\0')
			add_history(line);
		check_prompt(line, envp);
		//printf("%s\n", line);
		if (ft_strncmp("exit", line, 5) == 0)
			exit(0);
		if (ft_strncmp("$", line, 1) == 0)
			env(line + 1);
		if (ft_strncmp("pwd", line, 4) == 0)
			pwd();
		disp_next_prompt(&line);
	}
}
