/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:40 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/19 18:31:49 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_free_filelist(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
		free(tmp->filename);
		free(tmp);
	}
}

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
		if (cmd->str)
			free(cmd->str);
		if (cmd->infile)
			ms_free_filelist(cmd->infile);
		if (cmd->outfile)
			ms_free_filelist(cmd->outfile);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}
