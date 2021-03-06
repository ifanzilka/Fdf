/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:55:44 by bmarilli          #+#    #+#             */
/*   Updated: 2020/10/31 05:25:26 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Функция atoi() преобразует начальную часть строки, на которую указывает str,
** в представление int.
**
** RETURN
**
** Возвращает число
*/

static int	ft_sing(int sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *ptr)
{
	unsigned int	res;
	unsigned int	last_res;
	int				sign;

	res = 0;
	sign = 1;
	while ((9 <= *ptr && *ptr <= 13) || *ptr == 32)
		ptr++;
	if (*ptr == '-')
		sign = -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (ft_isdigit(*ptr))
	{
		last_res = res;
		res = res * 10 + *ptr - '0';
		if (last_res > res)
			return (ft_sing(sign));
		ptr++;
	}
	return (res * sign);
}
