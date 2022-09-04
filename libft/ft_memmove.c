/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:04:27 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/29 00:50:32 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if (!dst && !src)
		return (0);
	tmp_dst = dst;
	tmp_src = src;
	if (tmp_src < tmp_dst)
		while (len--)
			*(tmp_dst + len) = *(tmp_src + len);
	else
		while (len--)
			*tmp_dst++ = *tmp_src++;
	return (dst);
}
