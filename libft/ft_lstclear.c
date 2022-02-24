/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:51:36 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/13 16:47:56 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The adress of a pointer to an element.
//           #2. The adress of the function used to delete the content of the
//               element.
//Return value None
//External functs. free
//Description Deletes and frees the given element and every successor of that
//    element, using the function ’del’ and free(3). Finally, the pointer to
//    the list must be set to NULL.
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}
