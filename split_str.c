/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:53:59 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 17:42:29 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmdlen(char *line)
{
	int		quote;
	int		len;

	quote = 0;
	len = 0;
	if (!line)
		return (0);
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

static char	**ms_ret_empty(void)
{
	char	**cmds;

	cmds = malloc(sizeof(char *) * 2);
	cmds[0] = ft_strdup("");
	cmds[1] = NULL;
	return (cmds);
}

static char	**ms_split_str(char *line)
{
	char	**cmds;
	char	**tmp;
	char	*str;
	int		len;

	if (!line || ms_empty_string(line))
		return (ms_ret_empty());
	len = ms_cmdlen(line);
	cmds = malloc(sizeof(char *) * (len + 1));
	if (!cmds)
		ms_exit(EXIT_FAILURE);
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

void	ms_split(t_cmd *cmd)
{
	cmd->cmd = ms_split_str(cmd->str);
	free(cmd->str);
	cmd->str = NULL;
}
