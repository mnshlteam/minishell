/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:45:02 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/07 19:55:54 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isspace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r'
		|| ch == '\v' || ch == '\f');
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
