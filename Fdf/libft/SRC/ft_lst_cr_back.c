/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cr_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:09:44 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:34:01 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_cr_back(t_list **lst, void *content)
{
	t_list	*new;
	t_list	*cur;

	new = ft_lstnew(content);
	if (!(new))
		return (NULL);
	if (!lst)
		return (NULL);
	cur = *lst;
	if (!cur)
		*lst = new;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
