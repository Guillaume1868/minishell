/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 09:47:09 by gaubert          ###   ########.fr       */
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
	struct s_redir		*next;
	struct s_redir		*prev;
}	t_redir;

typedef struct s_cmd
{
	int				order;
	char			*name;
	char			**args;
	t_redir			*first_in_redir;
	t_redir			*first_out_redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

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

//parse.c
t_cmd			*parse(char *line, char **envp);

#endif
