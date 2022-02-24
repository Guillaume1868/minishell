/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:48:19 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/13 15:26:43 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The content to create the new element with.
//Return value The new element.
//External functs. malloc
//Description Allocates (with malloc(3)) and returns a new element. The
//    variable ’content’ is initialized with the value of the parameter
//    ’content’. The variable ’next’ is initialized to NULL.

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list *) malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}
