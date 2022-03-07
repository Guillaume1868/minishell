/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 12:59:11 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "builtin.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>

enum e_type{out, append_out, in, delim_in};


typedef struct s_redir
{
	int					type;
	char				*str;
	int					fd;
}	t_redir;

typedef struct s_cmd
{
	int				order;
	char			*name;
	t_list			*args;
	t_list			*in_redir;
	t_list			*out_redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_params
{
	char		*line;
	int			*i;
	char		*quote;
	t_cmd		*res;
}	t_params;

// wtf ?
void			rl_replace_line(const char *fuck, int c);

//main.c
void			check_prompt(char *line, char **envp);

typedef struct s_shell {
	pid_t			id;
	struct s_shell	*previous;
	struct s_shell	*next;
}				t_shell;

//env.c
char			*get_env(char *name, char **envp);

//find_exe.c
char			*get_executable_path(char *name, char **envp);

//parse_utils.c
int				is_seperator(char c);
char			*malloc_word(char *start, char *end);
int				quotes(char c, char *quote);
char			*get_word(char *line, int *i, char *quote);

//parse.c
t_list			*parse(char *line, char **envp);

#endif
