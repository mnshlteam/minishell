/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_cntl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:34:52 by yolee             #+#    #+#             */
/*   Updated: 2022/09/20 18:36:32 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_new_tmp_name(char tmp_name[255], int idx)
{
	tmp_name[idx]++;
	if (tmp_name[idx] == -128)
	{
		tmp_name[idx] = 1;
		get_new_tmp_name(tmp_name, idx + 1);
	}
}

static int	ms_heredoc(t_file *file)
{
	int		fd;
	char	tmp_name[255];
	char	*str;

	ft_bzero(tmp_name, 255);
	while (1)
	{
		fd = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
		if (fd == -1)
			get_new_tmp_name(tmp_name, 0);
		else
			break ;
	}

	while (ft_strncmp(str, file->filename, ft_strlen(file->filename) + 1))
	{
		str = readline("> ");
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	close(fd);
	fd = open(tmp_name, O_RDONLY);
	unlink(tmp_name);
	return (fd);
}

int	ms_open_infile(t_file *file)
{
	int	fd;

	while (file)
	{
		if (file->mode == MODE_READ)
			fd = open(file->filename, O_RDONLY);
		else if (file->mode == MODE_HEREDOC)
			fd = ms_heredoc(file);
		if (fd == -1)
			ms_exit("minishell: (filename): No such file or directory", 1);
		if (file->next)
			close(fd);
		file = file->next;
	}
	return (fd);
}
