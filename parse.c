/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:45:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 21:47:58 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_input_error(char *line)
{
	int	i;
	int	quote;

	quote = 0;
	while (*line)
	{
		quote = ms_quote_status(*line, quote);
		if ((*line == '\\' || *line == ';') && !quote)
		{
			ms_print_error("unexpected character `", line, "\'\n", 1);
			return (1);
		}
		line++;
	}
	if (quote)
	{
		write(2, "minishell: found unclosed quotes", 32);
		return (1);
	}
	return (0);
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
		write(2, "minishell: syntax error near unexpected token `|\'", 49);
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
		ms_exit(EXIT_FAILURE);
}

t_cmd	*ms_parse(char *line)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	if (ms_input_error(line))
		return (NULL);
	cmd = ms_new_cmd(NULL);
	if (!cmd)
		ms_exit(EXIT_FAILURE);
	tmp = cmd;
	ms_divide_line(cmd, line);
	while (cmd)
	{
		ms_parse_dollar(cmd);
		if (ms_parse_redirect(cmd))
			return (tmp);
		ms_split(cmd);
		cmd = cmd->next;
	}
	ms_execute_proc(tmp);
	return (tmp);
}
