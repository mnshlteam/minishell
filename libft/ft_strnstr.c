/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 00:46:01 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/22 03:06:34 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		i = 0;
		while (big[i] == little[i] && i < len)
		{
			i++;
			if (!little[i])
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (0);
}
