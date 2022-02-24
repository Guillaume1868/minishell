/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:49:04 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/13 15:32:25 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The beginning of the list.
//Return value Length of the list.
//External functs. None
//Description Counts the number of elements in a list.
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	i = 1;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
