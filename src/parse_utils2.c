/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:39:42 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/25 13:39:42 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	short_count(int *del, int *add)
{
	char	*tmp;

	tmp = ft_itoa(g_success);
	*del += 2;
	*add += ft_strlen(tmp) + 1;
	free(tmp);
}
