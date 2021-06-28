/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:40:32 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 18:40:45 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;

	if ((size + 1) < size)
		return (NULL);
	s = (char *)ft_memalloc(sizeof(char) * (size + 1));
	if (!(s))
		return (NULL);
	return (s);
}
