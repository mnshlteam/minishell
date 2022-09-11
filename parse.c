/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:45:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 01:40:06 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_input_error(char *line)
{
	int	quote;

	quote = 0;
	while (*line)
	{
		quote = ms_quote_status(*line, quote);
		if ((*line == '\\' || *line == ';') && !quote)
			ms_exit("minishell: unexpected character", 1);
		line++;
	}
	if (quote)
		ms_exit("minishell: found unclosed quotes", 1);
}

static char	*ms_replace_dollar(char **cmd)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	(*cmd)++;
	while (ft_isalnum((*cmd)[i]) || (*cmd)[i] == '_')
		i++;
	tmp = ft_substr(*cmd, 0, i);
	*cmd += i;
	str = ft_strdup(ms_getenv(tmp));
	free(tmp);
	return (str);
}

static char	*ms_parse_dollar(char *cmd, int mem)
{
	char	*str;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	if (!*cmd)
		return (NULL);
	if (*cmd == '$')
		return (ms_strjoin_free(ms_replace_dollar(&cmd), \
			ms_parse_dollar(cmd, 1)));
	while (cmd[i])
	{
		quote = ms_quote_status(cmd[i], quote);
		if (cmd[i] == '$' && quote != 1)
		{
			str = ft_substr(cmd, 0, i);
			cmd += i;
			return (ms_strjoin_free(str, ms_parse_dollar(cmd, 1)));
		}
		i++;
	}
	if (mem)
		return (ft_strdup(cmd));
	return (cmd);
}

static void	ms_divide_line(t_cmd *cmd, char *line)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (*line == ' ' || *line == '\t' || *line == '\r'
		|| *line == '\v' || *line == '\f')
		line++;
	while (line[i])
	{
		quote = ms_quote_status(line[i], quote);
		if (line[i] == '|' && !quote)
		{
			cmd->next = ms_new_cmd();
			ms_divide_line(cmd->next, line + i + 1);
			break ;
		}
		i++;
		if (cmd->next)
			cmd = cmd->next;
	}
	cmd->cmd = ft_substr(line, 0, i);
	if (!cmd->cmd)
		ms_exit("minishell: malloc error", 1);
}

// void	asdf(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("%s %s\n", cmd->cmd, cmd->param);
// 		cmd = cmd->next;
// 	}
// }

void	ms_parse(char *line)
{
	t_cmd	*cmd;

	ms_input_error(line);
	cmd = ms_new_cmd();
	ms_divide_line(cmd, line);
	while (cmd)
	{
		cmd->cmd = ms_parse_dollar(cmd->cmd, 0);
		cmd = cmd->next;
	}
}
