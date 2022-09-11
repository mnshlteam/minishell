/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:35:03 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 01:36:16 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ms_exit("minishell: malloc error", 1);
	cmd->cmd = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->fd[0] = 0;
	cmd->fd[1] = 0;
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
