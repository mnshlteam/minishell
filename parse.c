/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:45:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 20:19:30 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_input_error(char *line)
{
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
		write(2, "minishell: found unclosed quotes\n", 33);
		return (1);
	}
	return (0);
}

static int	ms_unexpected_pipe(void)
{
	write(2, "minishell: syntax error near unexpected token `|\'\n", 50);
	g_config.exit_status = 258;
	return (1);
}

static int	ms_divide_line(t_cmd *cmd, char *line, int quote)
{
	int		i;

	i = 0;
	while (ms_isspace(*line))
		line++;
	if (*line == '|')
		return (ms_unexpected_pipe());
	while (line[i])
	{
		quote = ms_quote_status(line[i], quote);
		if (line[i] == '|' && !quote)
		{
			cmd->next = ms_new_cmd(cmd);
			if (ms_divide_line(cmd->next, line + i + 1, 0))
				return (1);
			break ;
		}
		i++;
		cmd = ms_nextifcan(cmd);
	}
	cmd->str = ft_substr(line, 0, i);
	if (!cmd->str)
		ms_exit(EXIT_FAILURE);
	return (0);
}

static void	ms_parse_loop(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		ms_parse_dollar(cmd);
		if (ms_parse_redirect(cmd))
		{
			g_config.exit_status = 258;
			return ;
		}
		ms_split(cmd);
		cmd = cmd->next;
	}
	ms_execute_proc(tmp);
}

t_cmd	*ms_parse(char *line)
{
	t_cmd	*cmd;

	if (ms_input_error(line))
	{
		g_config.exit_status = 258;
		return (NULL);
	}
	cmd = ms_new_cmd(NULL);
	if (!cmd)
		ms_exit(EXIT_FAILURE);
	if (ms_divide_line(cmd, line, 0))
		return (cmd);
	ms_parse_loop(cmd);
	return (cmd);
}
