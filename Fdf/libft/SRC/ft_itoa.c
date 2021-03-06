/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:12:27 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 20:23:18 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Описание выделяет (с помощью malloc(3)) и возвращает строку
**  представляющую целое число, полученное в качестве аргумента.
**
** RETURN
**
** Cтрока, представляющая целое число. NULL, если
** выделение не удается.
*/

static int	ft_cnt_len_str(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	long	nn;

	nn = n;
	len = ft_cnt_len_str(n);
	s = (char *)malloc(len + 1);
	if (!(s))
		return (NULL);
	s[len] = '\0';
	if (nn < 0)
	{
		s[0] = '-';
		nn = -nn;
	}
	else if (nn == 0)
	{
		s[0] = '0';
	}
	while (nn > 0)
	{
		s[--len] = '0' + nn % 10;
		nn /= 10;
	}
	return (s);
}
