/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:50:43 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 11:12:52 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The element to free.
//           #2. The address of the function used to delete the content.
//Return value None
//External functs. free
//Description Takes as a parameter an element and frees the memory of the
//    element’s content using the function ’del’ given as a parameter and free
//    the element. The memory of ’next’ must not be freed.
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
