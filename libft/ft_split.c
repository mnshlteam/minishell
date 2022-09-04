/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:12:37 by hyejo             #+#    #+#             */
/*   Updated: 2021/12/05 18:19:21 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_return(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
	return (0);
}

static char	*ft_set_word(char const *str, int size)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (0);
	i = 0;
	while (i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static int	ft_get_word_len(char const *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static char	**ft_set_result(char const *str, char c, int len)
{
	char	**result;
	char	**tmp;
	char	*word;
	int		word_len;

	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (0);
	tmp = result;
	while (len)
	{
		word_len = ft_get_word_len(str, c);
		if (word_len != 0)
		{
			word = ft_set_word(str, word_len);
			if (!word)
				return (ft_free_return(result));
			*tmp++ = word;
			len--;
		}
		str += word_len + 1;
	}
	*tmp = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	len;
	int		i;

	if (!s)
		return (0);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (!s[i + 1] || s[i + 1] == c))
			len++;
		i++;
	}
	result = ft_set_result(s, c, len);
	if (!result)
		return (0);
	return (result);
}
