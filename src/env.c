/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:18:03 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/01 12:18:20 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char *var)
{
	char	*res;

	printf("search env '%s'\n", var);
	res = getenv(var);
	if (res != NULL)
		printf("%s=%s\n", var, res);
	else
		printf("env %s not found\n", var);
}