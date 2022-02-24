/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:53:27 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 10:27:33 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parameters #1. The adress of a pointer to an element.
//           #2. The adress of the function used to iterate on the list.
//           #3. The adress of the function used to delete the content of an
//               element if needed.
//Return value The new list. NULL if the allocation fails.
//External functs. malloc, free
//Description Iterates the list ’lst’ and applies the function ’f’ to the
//    content of each element. Creates a new list resulting of the successive
//    applications of the function ’f’. The ’del’ function is used to delete the
//    content of an element if needed.
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		ft_lstclear(&res, del);
	if (!res)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&new, del);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
