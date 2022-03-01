/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:01:53 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/01 14:13:37 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *args)
{
	if (args == NULL)
		ft_putstr_fd("minishell: expected argument to \"cd\"\n", 1);
	else
	{
		if (chdir(args) != 0)
			printf("cd: %s: No such file or directory\n", args);
	}
	return (1);
}

int	ft_help(void)
{
	printf("HELP OF MINISHELL\nThe following are built in: cd help exit\n"
		"Use the man command for information on other programs.\n");
	return (1);
}

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
