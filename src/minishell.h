/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 18:03:52 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

enum e_type{out, append_out, in, delim_in};

int	g_success;

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
void			pwd(void);
void			ft_echo(char **args);
void			free_envp(char **envp);

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

typedef struct s_exec
{
	char		**args;
	char		*path;
	int			*link;
	int			nbr_pipes;
	int			counter;
	t_list		*tmp;
	t_list		**cmd_lst_tofree;
	pid_t		*pid;
}				t_exec;

//file_edit.c
void			ft_heredoc(t_list *tmp, t_exec *exec, int i);
void			exec_stdin(t_list *cmd_lst, t_exec *exec, int i);
void			exec_stdout(t_list *cmd_lst, t_exec *exec, int i);
void			count_pipes(t_exec *exec, t_list *cmd_lst);
void			change_pip(int *pip, int i, t_exec *exec);

//execution.c
char			**execute_program(char *path, t_list *args, char **envp);
void			child_program(t_list *cmd_lst, t_exec *exec, int i,
					char **envp);
void			pid_equal_zero(t_list *cmd_lst, t_exec *exec, char	**envp,
					char *tmp);
char			**itering_prog(char *path, t_list *cmd_lst, t_exec *exec,
					char **envp);

//functions.c
char			**ft_export(char **envp, char *args);
char			**make_export(char **envp, char *args, char *tmp, int i);
char			**ft_unset(char **envp, char *args, t_exec *exec);
char			*ft_strjoinfree(char *s1, char *s2);

//functions2.c
char			**recreate_envp(char **envp, int i, int ismalloc);
int				check_builtin_forked(char *cmd, char **args, char **envp);
char			**check_builtin(char *cmd, char *args, char **envp,
					t_exec *exec);

//builtin.c
int				ft_cd(char *args, char **envp);
void			ft_help(void);
int				ft_exit(char **envp, t_exec *exec);
void			ft_env(char	**envp);

//fill_word.c
void			fill_word(char *res, char *line, char **envp, int *i);
int				quotes(char c, char *quote);

//free.c
int				ft_cmdfree(t_list *cmd_lst);
int				f_free(void *ptr);

//free2.c
int				f_exit(int i);

#endif
