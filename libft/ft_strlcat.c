/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:36:05 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/22 02:54:53 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize && *dst)
	{
		dst++;
		i++;
	}
	while (i + 1 < dstsize && *src)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	if (i < dstsize)
		*dst = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
