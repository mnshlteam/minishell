/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:45:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/20 19:09:58 by yolee            ###   ########.fr       */
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
// 	char	**argv;
// 	t_file	*file;

// 	printf("===========\n");
// 	while (cmd)
// 	{
// 		argv = cmd->cmd;
// 		while (*argv)
// 			printf("%s\n", *argv++);
// 		printf("-----------\n");
// 		file = cmd->infile;
// 		while (file)
// 		{
// 			printf("input: %s %d\n", file->filename, file->mode);
// 			file = file->next;
// 		}
// 		file = cmd->outfile;
// 		while (file)
// 		{
// 			printf("output: %s %d\n", file->filename, file->mode);
// 			file = file->next;
// 		}
// 		printf("-----------\n");
// 		cmd = cmd->next;
// 	}
// }

t_cmd	*ms_parse(char *line)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	ms_input_error(line);
	cmd = ms_new_cmd(NULL);
	if (!cmd)
		ms_exit("minishell: malloc error", 1);
	tmp = cmd;
	ms_divide_line(cmd, line);
	while (cmd)
	{
		ms_parse_dollar(cmd);
		ms_parse_redirect(cmd);
		ms_split(cmd);
		cmd = cmd->next;
	}
	ms_execute_proc(tmp);
	return (tmp);
}
