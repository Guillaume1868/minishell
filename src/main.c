/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 14:01:25 by gaubert          ###   ########.fr       */
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
		printf("%s\n", dir);
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

void	check_prompt(char *line, char **envp)
{
	int		i;
	char	*argument;
	char	*path;

	i = 0;
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
	else if (ft_strncmp(line, "echo", i) == 0)
		ft_echo(argument);
	else if (ft_strncmp(line, "$", 1) == 0)
		printf("%s\n", get_env(line + 1, envp));
	else if (ft_strncmp(line, "env", i) == 0)
		ft_env(envp);
	else if (ft_strncmp(line, "pwd", i) == 0)
		pwd();
	else if (line[0] != '\0')
	{
		path = get_executable_path(&line[0], envp);
		if (path)
		{
			printf("%s\n", path);
		}
		else
			printf("minishell: %s command not found\n", line);
		free(path);
	}
}
void	printff(void *arg)
{
	printf("- %s\n", (char *)arg);
}

void	printredir(void *arg)
{
	t_redir	*tmp;

	tmp = arg;
	printf("|%s| type=%d\n", tmp->str, tmp->type);
}

void	printcmd(void *param)
{
	t_cmd	*cmd;

	cmd = param;
	if (cmd->pipe_from_prec)
		printf("==========\n%sPIPED command:%s\n", KRED, KNRM);
	else
		printf("==========\n%scommand:%s\n", KYEL, KNRM);
	printff(cmd->name);
	if (cmd->args)
		printf("args:\n");
	ft_lstiter(cmd->args, printff);
	if (cmd->in_redir)
		printf("in redirs:\n");
	ft_lstiter(cmd->in_redir, printredir);
	if (cmd->out_redir)
		printf("out redirs:\n");
	ft_lstiter(cmd->out_redir, printredir);
	printf("==========\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*cmd_lst;

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
		{
			add_history(line);
			cmd_lst = parse(line, envp);
			ft_lstiter(cmd_lst, printcmd);
		}
		disp_next_prompt(&line);
	}
	//redire a vbotev si jarrive a print le exit
}
