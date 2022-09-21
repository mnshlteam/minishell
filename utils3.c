/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:40 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 21:49:29 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_empty_string(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ms_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ms_print_error(char *s1, char *s2, char *s3, int s2len)
{
	write(2, "minishell: ", 11);
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
	{
		if (s2len)
			write(2, s2, s2len);
		else
			write(2, s2, ft_strlen(s2));
	}
	if (s3)
		write(2, s3, ft_strlen(s3));
}

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
