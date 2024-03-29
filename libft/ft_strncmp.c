/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:30:46 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/22 16:28:34 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	i = 0;
	while (i < n && *tmp1 && *tmp2)
	{
		if (*tmp1 != *tmp2)
			break ;
		tmp1++;
		tmp2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*tmp1 - *tmp2);
}
