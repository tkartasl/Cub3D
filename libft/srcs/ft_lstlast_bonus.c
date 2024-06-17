/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:09:23 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/10 12:39:06 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	t_list	*ret;

	if (lst == 0)
		return (lst);
	ret = NULL;
	current = lst;
	while (current != 0)
	{
		ret = current;
		current = current->next;
	}
	return (ret);
}
