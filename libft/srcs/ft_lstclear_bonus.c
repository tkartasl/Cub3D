/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:10 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/10 12:37:31 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	temp = NULL;
	while (current != 0)
	{
		temp = current->next;
		del(current->content);
		free(current);
		current = temp;
	}
	*lst = NULL;
}
