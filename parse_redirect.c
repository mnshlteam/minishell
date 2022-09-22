/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:10:56 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/22 15:55:24 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_redirect_error(char *line)
{
	char	ch;
	char	cmp;
	int		i;

	ch = *line++;
	cmp = '>';
	if (ch == '>')
		cmp = '<';
	i = 0;
	while (*line)
	{
		if (*line == cmp)
		{
			ms_print_error("syntax error near unexpected token `",
				line, "\'\n", 1);
			return (1);
		}
		else if (*line == ch)
			i++;
		else if (*line != ' ')
			break ;
		line++;
	}
	if (!line || *line == '>' || *line == '<' || *line == '|' || i > 1)
	{
		ms_print_error("syntax error near unexpected token `", line, "\'\n", 1);
		return (1);
	}
	return (0);
}

static void	ms_handle_redirect(t_cmd *cmd, char **line)
{
	char	*str;
	char	ch;
	int		i;
	int		len;

	ms_redirect_error(*line);
	i = -1;
	ch = **line;
	while (**line == ch)
	{
		i++;
		(*line)++;
	}
	while (**line == ' ')
		(*line)++;
	len = 0;
	while ((*line)[len] && (*line)[len] != ' '
		&& (*line)[len] != '>' && (*line)[len] != '<')
		len++;
	str = ft_substr(*line, 0, len);
	ms_add_last_file(cmd, str, i, ch == '>');
	(*line) += len;
}

static char	*ms_parse_red_str(t_cmd *cmd, char *line, int quote)
{
	char	*str;
	int		i;

	if (!line || !*line)
		return (NULL);
	if (*line == '>' || *line == '<')
	{
		ms_handle_redirect(cmd, &line);
		return (ms_parse_red_str(cmd, line, quote));
	}
	i = 0;
	while (line[i])
	{
		quote = ms_quote_status(line[i], quote);
		if ((line[i] == '>' || line[i] == '<') && !quote)
		{
			str = ft_substr(line, 0, i);
			line += i;
			ms_handle_redirect(cmd, &line);
			return (ms_strjoin_free(str, ms_parse_red_str(cmd, line, quote)));
		}
		i++;
	}
	return (ft_strdup(line));
}

int	ms_parse_redirect(t_cmd *cmd)
{
	char	*str;

	str = ms_parse_red_str(cmd, cmd->str, 0);
	free(cmd->str);
	cmd->str = str;
	return (0);
}
