/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/07 14:10:47 by gaubert          ###   ########.fr       */
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

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

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
	int				pipe_from_prec;
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

//debug.c
void			print_lst(void *arg);
void			print_redir(void *arg);
void			print_cmd(void *param);

#endif
