/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:33:59 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/22 00:46:15 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_len(int n)
{
	int	len;

	if (0 < n)
		len = 0;
	else
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = ft_get_len(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len--] = 0;
	while (0 <= len)
	{
		str[len--] = '0' + n % 10 * sign;
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
