/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:00:58 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/04 17:38:02 by gaubert          ###   ########.fr       */
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

static int	quotes(char c, char *quote)
{
	if (*quote == '0' && (c == '\'' || c == '\"'))
		*quote = c;
	else if (*quote != '0' && c == *quote)
	{
		*quote = '0';
		return(0);
	}
	return (1);
}

char *make_cmd(char *start, char *end)
{
	char	quote;
	int		i;
	char	*res;
	int		count;

	//printf("\nmaking command:\n");
	quote = '0';
	i = -1;
	count = 0;
	while (start + ++i <= end)
	{
		quotes(*(start + i), &quote);
		if (*(start + i) != quote)
			count++;
		//printf("%c", *(start + i));
	}
	res = ft_calloc(sizeof(char), count + 1);
	i = -1;
	count = -1;
	quote = '0';
	while (start + ++i <= end)
	{
		//quotes(*(start + i), &quote);
		if (quotes(*(start + i), &quote) && *(start + i) != quote)
			res[++count] = start[i];
	}
	//printf("\n------------\n");
	printf("res=|%s|\n", res);
	return (res);
}

t_cmd	*parse(char *line, char **envp)
{
	t_cmd	*res;
	int		i;
	char	quote = '0';
	char	*start, *end;

	(void)envp;
	(void)res;
	i = 0;
	res = (void *)ft_calloc(1, sizeof(t_cmd));
	while (line[i])
	{
		//printf("|%s|\n", &line[i]);
		quotes(line[i], &quote);
		//printf("quote:%c reading:%c\n", quote, line[i]);
		if (quote == '0' && (line[i] == '<' || line[i] == '>'))
		{
			//printf("==================\nin a redirector\n");
			if (line[i] == '<')
			{
				i++;
				if (line[i + 1] == '<')
				{
					printf("<<\n");
i++;
				}
				else
					printf("<\n");
			}
			else if (line[i] == '>')
			{
				i++;
				if (line[i + 1] == '>')
				{
i++;
					printf(">>\n");
				}
				else
					printf(">\n");
			}
		}
		else if (line[i] != ' ')
		{
			//printf("==================\nin a command\n");
			start = &line[i];
			while (line[i] != 0 && !(line[i] == ' ' && quote == '0'))
			{
				//printf("%c", line[i]);
				i++;
				quotes(line[i], &quote);
			}
			end = &line[i - 1];
			res->name = make_cmd(start, end);
			//printf("\n==================\ncommand finished\n");
		}
		else
			i++;
	}
	//return (&res);
	return(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

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
			//check_prompt(line, envp);
			cmd = parse(line, envp);
		}
		//printf("%s\n", line);
		disp_next_prompt(&line);
	}
	//redire a vbotev si jarrive a print le exit
}
