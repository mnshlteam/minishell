/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:45:02 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 01:32:27 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isspace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r'
		|| ch == '\v' || ch == '\f');
}

char	*ms_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	*str_to_env(char *str)
{
	char	*value;

	value = ft_strdup(ms_getenv(str));
	free(str);
	return (value);
}

char	*ms_join_words(char **words)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (*words)
	{
		tmp = str;
		if (tmp)
		{
			str = ft_strjoin(tmp, *words);
			free(tmp);
		}
		else
			str = ft_strdup(*words);
		words++;
	}
	return (str);
}

void	free_strlist(char **strlist)
{
	char	**tmp;

	tmp = strlist;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
}
