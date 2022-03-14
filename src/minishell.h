/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/14 13:01:43 by gaubert          ###   ########.fr       */
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
	int			type;
	char		*str;
}	t_redir;

typedef struct s_cmd
{
	t_list		*args;
	t_list		*in_redir;
	t_list		*out_redir;
	int			pipe_from_prec;
}	t_cmd;

typedef struct s_params
{
	char		*line;
	int			*i;
	char		*quote;
	t_cmd		*cmd;
	t_list		*c;
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
char			*get_env_2(char *name, char **envp);

//find_exe.c
char			*get_executable_path(char *name, char **envp);

//parse_utils.c
int				is_seperator(char c);
char			*malloc_word(char *start, char *end);
char			*get_word(char *line, int *i, char *quote, char **envp);

//parse.c
t_list			*parse(char *line, char **envp);
int				save_redir(t_params p, enum e_type t, int mode, char **envp);

//parse2.c
void			pack_p(t_params *p, int *i, char *line, char *quote);
void			redir(t_params *p, char *linei, char **envp);
void			add_cmd(t_params *p);
void			add_word(t_params *p, char **envp);
//debug.c
void			print_lst(void *arg);
void			print_redir(void *arg);
void			print_cmd(void *param);

//fill_word.c
void			fill_word(char *res, char *line, char **envp, int *i);
int				quotes(char c, char *quote);

//free.c
int				ft_cmdfree(t_list *cmd_lst);
int				f_free(void *ptr);

//free2.c
int				f_exit(int i);

#endif
