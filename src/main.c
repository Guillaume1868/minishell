/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/23 12:03:47 by gaubert          ###   ########.fr       */
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
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	pwd(void) //TODO: move dans builtin ?
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
	*line = readline ("\033[36;1m$>\033[0m");
}

void	ft_echo(char *argument) //TODO: move dans builtin ?
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

void	ft_short()
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*cmd_lst;
	char		*path;
	int			i;

	ft_short();
	path = NULL;
	if (argc == 2)
	{
		cmd_lst = parse(argv[1], envp);
		ft_lstiter(cmd_lst, print_cmd);
		ft_cmdfree(cmd_lst);
		exit (0);
	}
	line = readline ("\033[36;1m$>\033[0m");
	i = 0;
	while (envp[i])
		i++;
	envp = recreate_envp(envp, i, 0);
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			cmd_lst = parse(line, envp);
			ft_lstiter(cmd_lst, print_cmd);
			//path = get_executable_path(&line[0], envp);
			envp = execute_program(path, cmd_lst, envp);
			//free(path);
		}
		disp_next_prompt(&line);
	}
}
