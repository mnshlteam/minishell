/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:53:59 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 18:55:58 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmdlen(char *line)
{
	int		quote;
	int		len;

	quote = 0;
	len = 0;
	while (*line)
	{
		quote = ms_quote_status(*line, quote);
		if (!quote && *line && !ms_isspace(*line)
			&& (ms_isspace(*(line + 1)) || !*(line + 1)))
			len++;
		line++;
	}
	return (len);
}

static char	*ms_put_cmd(char **line)
{
	int		quote;
	int		len;
	char	*cmd;
	char	*tmp;

	quote = 0;
	len = 0;
	while ((*line)[len])
	{
		quote = ms_quote_status((*line)[len], quote);
		if (!quote && (*line)[len] && !ms_isspace((*line)[len])
			&& (ms_isspace((*line)[len + 1]) || !(*line)[len + 1]))
			break ;
		len++;
	}
	tmp = ft_substr(*line, 0, len + 1);
	*line += len + 1;
	cmd = ms_parse_quotes(tmp);
	free(tmp);
	return (cmd);
}

char	**ms_split_str(char *line)
{
	char	**cmds;
	char	**tmp;
	char	*str;
	int		len;

	if (!line)
		return (NULL);
	len = ms_cmdlen(line);
	cmds = malloc(sizeof(char *) * (len + 1));
	if (!cmds)
		ms_exit("minishell: malloc error", 1);
	tmp = cmds;
	while (len--)
	{
		while (ms_isspace(*line))
			line++;
		str = ms_put_cmd(&line);
		*tmp = str;
		tmp++;
	}
	*tmp = NULL;
	return (cmds);
}
