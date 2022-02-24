/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:04:23 by gaubert           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/02/24 16:20:13 by gaubert          ###   ########.fr       */
=======
/*   Updated: 2022/02/24 14:56:16 by gaubert          ###   ########.fr       */
>>>>>>> 8d987a9a1d9351d061fc3023d360d74946713b61
=======
/*   Updated: 2022/02/24 16:20:17 by gaubert          ###   ########.fr       */
>>>>>>> a81d739fa62ad0385f2bfe516f8a8abec8ab803e
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "builtin.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

// wtf ?
void			rl_replace_line(const char *fuck, int c);
typedef struct s_shell {
	pid_t	id;
	t_shell	*previous;
	t_shell	*next;
}				t_shell;

#endif
