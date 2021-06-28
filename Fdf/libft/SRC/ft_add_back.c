/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:45:06 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 20:45:48 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_add_back(char **str, char c, int n)
{
	char	*tmp;
	char	*tmp2;

	tmp = (ft_create_str(c, n));
	if (!(tmp) || !*str)
		return (-1);
	tmp2 = *str;
	*str = ft_strjoin(tmp2, tmp);
	if (!(str))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	free(tmp2);
	return (1);
}
