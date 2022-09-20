/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:10:56 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/19 18:27:08 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_redirect_error(char *line)
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
			ms_exit("minishell: syntax error near unexpected token", 258);
		else if (*line == ch)
			i++;
		else if (*line != ' ')
			break ;
		line++;
	}
	if (!line || *line == '>' || *line == '<' || *line == '|' || i > 1)
		ms_exit("minishell: syntax error near unexpected token", 258);
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

void	ms_parse_redirect(t_cmd *cmd)
{
	char	*str;

	str = ms_parse_red_str(cmd, cmd->str, 0);
	free(cmd->str);
	cmd->str = str;
}