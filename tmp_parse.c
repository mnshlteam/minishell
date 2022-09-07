/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:38:40 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/07 19:59:21 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 임시 파싱 함수

#include "minishell.h"

char	*str_to_env(char *str)
{
	char	*value;

	value = ft_strdup(ms_getenv(str));
	free(str);
	return (value);
}

char	**tmp_read_dollar(char **cmds)
{
	char	**strs;
	char	**words;
	char	**tmp;

	strs = cmds;
	while (*strs)
	{
		if (**strs == '$')
		{
			words = ft_split(*strs, '$');
			tmp = words;
			while (*tmp)
			{
				*tmp = str_to_env(*tmp);
				tmp++;
			}
			free(*strs);
			*strs = ms_join_words(words);
			free_strlist(words);
			free(words);
		}
		strs++;
	}
	return (cmds);
}

void	tmp_parse(char *line)
{
	char	**cmds;

	while (*line == ' ' || *line == '\t' || *line == '\r'
		|| *line == '\v' || *line == '\f')
		line++;
	if (!*line)
		return ;
	cmds = ft_split(line, ' ');
	cmds = tmp_read_dollar(cmds);
	ms_execute(cmds);
	free_strlist(cmds);
	free(cmds);
}
