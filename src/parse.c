#include "minishell.h"

void	skip_space(char *str, int *i)
{
	while(str[*i] == ' ')
		*i = *i + 1;
}

void	save_redir(t_params p, enum e_type type, int in_mode)
{
	t_redir	*tmp;

	if (type == append_out || type == delim_in)
		*p.i = *p.i + 2;
	else
		*p.i = *p.i + 1;
	skip_space(p.line, p.i);
	tmp = malloc(sizeof(t_redir));
	tmp->str = get_word(p.line, p.i, p.quote);
	tmp->type = type;
	if (in_mode)
		ft_lstadd_back(&p.res->in_redir, ft_lstnew(tmp));
	else
		ft_lstadd_back(&p.res->out_redir, ft_lstnew(tmp));
}

t_list	*parse(char *line, char **envp)
{
	t_list		*c;
	t_cmd		*cmd;
	int			i;
	char		quote = '0';
	t_params	p;

	(void)envp;
	i = 0;
	cmd = (void *)ft_calloc(1, sizeof(t_cmd));
	ft_lstadd_back(&c, ft_lstnew(cmd));
	p.i = &i;
	p.line = line;
	p.quote = &quote;
	p.res = cmd;
	while (line[i])
	{
		quotes(line[i], &quote);
		if (quote == '0' && line[i] == ';')
		{
			i++;
			printf(";\n");
			cmd = (void *)ft_calloc(1, sizeof(t_cmd));
			ft_lstadd_back(&c, ft_lstnew(cmd));
			p.res = cmd;
		}
		else if (quote == '0' && line[i] == '|')
		{
			i++;
			printf("|\n");
		}
		else if (quote == '0' && (line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '<' && line[i + 1] == '<')
				save_redir(p, delim_in, 1);
			else if (line[i] == '<')
				save_redir(p, in, 1);
			else if (line[i] == '>' && line[i + 1] == '>')
				save_redir(p, append_out, 0);
			else if (line[i] == '>')
				save_redir(p, out, 0);
		}
		else if (line[i] != ' ')	//command
		{
			if (cmd->name == NULL)
				cmd->name = get_word(line, &i, &quote);
			else
			{
				ft_lstadd_back(&cmd->args, ft_lstnew(get_word(line, &i, &quote)));
			}
		}
		else
			i++;
	}
	return (c);
}