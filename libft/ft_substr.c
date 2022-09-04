/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:45:45 by hyejo             #+#    #+#             */
/*   Updated: 2021/11/23 02:47:09 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		*str = 0;
		return (str);
	}
	strlen = ft_strlen(s + start);
	if (len < strlen)
		strlen = len;
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
