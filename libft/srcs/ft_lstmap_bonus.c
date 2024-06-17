/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:02:26 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/10 14:34:12 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static t_list	*lstfirst(void *p, void *(*f)(void *), void (*del)(void *))
{
	void	*data;
	t_list	*new;

	data = f(p);
	new = ft_lstnew(data);
	if (new == 0)
	{
		del(data);
		free(new);
		return (0);
	}
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*headnew;
	void	*data;

	if (!lst || !f || !del)
		return (0);
	headnew = lstfirst(lst->content, f, del);
	if (headnew == 0)
		return (0);
	new = headnew;
	lst = lst->next;
	while (lst != 0)
	{
		data = f(lst->content);
		new->next = ft_lstnew(data);
		if (new->next == 0)
		{
			del(data);
			ft_lstclear(&headnew, del);
			return (0);
		}
		lst = lst->next;
		new = new->next;
	}
	return (headnew);
}
