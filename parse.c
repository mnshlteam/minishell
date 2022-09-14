/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:45:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/14 21:28:18 by hyejo            ###   ########.fr       */
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
	if (!ft_strlen(tmp))
		str = ft_strdup("$");
	else
		str = ft_strdup(ms_getenv(tmp));
	free(tmp);
	return (str);
}

static char	*ms_parse_dollar(char *cmd, int quote)
{
	char	*str;
	int		i;

	i = 0;
	if (!*cmd)
		return (NULL);
	if (*cmd == '$')
		return (ms_strjoin_free(ms_replace_dollar(&cmd), \
			ms_parse_dollar(cmd, quote)));
	while (cmd[i])
	{
		quote = ms_quote_status(cmd[i], quote);
		if (cmd[i] == '$' && quote != 1)
		{
			str = ft_substr(cmd, 0, i);
			cmd += i;
			return (ms_strjoin_free(str, ms_parse_dollar(cmd, quote)));
		}
		i++;
	}
	return (ft_strdup(cmd));
}

static void	ms_divide_line(t_cmd *cmd, char *line)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (ms_isspace(*line))
		line++;
	if (*line == '|')
		ms_exit("minishell: syntax error near unexpected token |", 258);
	while (line[i])
	{
		quote = ms_quote_status(line[i], quote);
		if (line[i] == '|' && !quote)
		{
			cmd->next = ms_new_cmd(cmd);
			ms_divide_line(cmd->next, line + i + 1);
			break ;
		}
		i++;
		if (cmd->next)
			cmd = cmd->next;
	}
	cmd->str = ft_substr(line, 0, i);
	if (!cmd->str)
		ms_exit("minishell: malloc error", 1);
}

// void	asdf(t_cmd *cmd)
// {
// 	char	*str;

// 	while (cmd)
// 	{
// 		str = *cmd->cmd;
// 		while (*str)
// 			printf("%s\n", str++);
// 		cmd = cmd->next;
// 	}
// }

t_cmd	*ms_parse(char *line)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	char	*str;

	ms_input_error(line);
	cmd = ms_new_cmd(NULL);
	if (!cmd)
		ms_exit("minishell: malloc error", 1);
	tmp = cmd;
	ms_divide_line(cmd, line);
	while (cmd)
	{
		str = ms_parse_dollar(cmd->str, 0);
		free(cmd->str);
		cmd->str = str;
		str = ms_parse_redirect(cmd, cmd->str, 0);
		free(cmd->str);
		cmd->str = str;
		cmd->cmd = ms_split_str(cmd->str);
		free(cmd->str);
		cmd->str = NULL;
		cmd = cmd->next;
	}
	return (tmp);
}
