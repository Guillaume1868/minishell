#include "minishell.h"

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
		quotes(line[i], &quote);
		if (quote == '0' && line[i] == ';')
		{
			i++;
			printf(";\n");
		}
		else if (quote == '0' && line[i] == '|')
		{
			i++;
			printf("|\n");
		}
		else if (quote == '0' && (line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				i += 2;
				printf("<<\n");
			}
			else if (line[i] == '<')
			{
				i++;
				printf("<\n");
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				i += 2;
				printf(">>\n");
			}
			else if (line[i] == '>')
			{
				i++;
				printf(">\n");
			}
		}
		else if (line[i] != ' ')	//command
		{
			start = &line[i];
			while (line[i] != 0 && !(is_seperator(line[i]) && quote == '0'))
			{
				i++;
				quotes(line[i], &quote);
			}
			end = &line[i - 1];
			res->name = malloc_word(start, end);
		}
		else
			i++;
	}
	return (res);
}