/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:35:03 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/19 17:45:58 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*ms_new_file(char *filename, int mode)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		ms_exit("minishell: malloc error", 1);
	file->filename = filename;
	file->mode = mode;
	file->next = NULL;
	return (file);
}

void	ms_add_last_file(t_cmd *cmd, char *filename, int mode, int io)
{
	t_file	*tmp;

	if (!io)
	{
		if (!cmd->infile)
		{
			cmd->infile = ms_new_file(filename, mode);
			return ;
		}
		else
			tmp = cmd->infile;
	}
	else
	{
		if (!cmd->outfile)
		{
			cmd->outfile = ms_new_file(filename, mode);
			return ;
		}
		else
			tmp = cmd->outfile;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ms_new_file(filename, mode);
}

t_cmd	*ms_new_cmd(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ms_exit("minishell: malloc error", 1);
	cmd->cmd = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	if (!prev || prev->index == 1)
		cmd->index = 0;
	else
		cmd->index = 1;
	cmd->next = NULL;
	cmd->prev = prev;
	return (cmd);
}

int	ms_quote_status(char ch, int quote)
{
	if (ch == '\'')
	{
		if (quote == 0)
			return (1);
		else if (quote == 1)
			return (0);
	}
	else if (ch == '\"')
	{
		if (quote == 0)
			return (2);
		else if (quote == 2)
			return (0);
	}
	return (quote);
}
