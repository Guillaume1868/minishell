/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:01:53 by gaubert           #+#    #+#             */
/*   Updated: 2022/02/24 16:45:50 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	(*builtin_func[]) (char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit
};*/

int	ft_cd(char **args)
{
	if (args[1] == NULL)
		ft_putstr_fd("lsh: expected argument to \"cd\"\n", 1);
	else
	{
		if (chdir(args[1]) != 0)
		{
			ft_putstr_fd("cd: ", 1);
			ft_putstr_fd(args[1], 1);
			ft_putstr_fd(": No such file or directory", 1);
		}
	}
	return (1);
}

int	ft_help(void)
{
	int	i;

	ft_putstr_fd("HELP OF MINISHELL\n", 1);
	ft_putstr_fd("The following are built in:\n", 1);
	i = 0;
	ft_putstr_fd("cd help exit\n", 1);
	ft_putstr_fd("\n", 1);
	i++;
	ft_putstr_fd("Use the man command for information on other programs.\n", 1);
	return (1);
}

int	ft_exit(void)
{
	return (0);
}
