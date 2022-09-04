/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:47:21 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/30 15:50:39 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n'
		|| ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		num *= 10;
		num += (*str - '0') * sign;
		if (num > 2147483647)
			return (-1);
		if (num < -2147483648)
			return (0);
		str++;
	}
	return (num);
}
