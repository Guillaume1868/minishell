/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/02 14:38:52 by gaubert          ###   ########.fr       */
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

#endif
