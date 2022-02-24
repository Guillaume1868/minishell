/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:50 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/13 16:40:33 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The address of a pointer to the first link of a list. #2. The
//    address of a pointer to the element to be added to the list.
//Return value None
//External functs. None
//Description Adds the element ’new’ at the beginning of the list.
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
