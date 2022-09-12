/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:35:03 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 18:23:56 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd)
		{
			free_strlist(cmd->cmd);
			free(cmd->cmd);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
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
