/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_cntl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:34:52 by yolee             #+#    #+#             */
/*   Updated: 2022/09/22 16:48:53 by yolee            ###   ########.fr       */
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

static int	open_with_tmp_name(char tmp_name[255])
{
	int	fd;

	while (1)
	{
		fd = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
		if (fd == -1)
			get_new_tmp_name(tmp_name, 0);
		else
			break ;
	}
	return (fd);
}

static int	ms_heredoc(t_file *file)
{
	int		fd;
	char	tmp_name[255];
	char	*str;

	ft_bzero(tmp_name, 255);
	fd = open_with_tmp_name(tmp_name);
	str = "";
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(str, file->filename, ft_strlen(file->filename) + 1))
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	fd = open(tmp_name, O_RDONLY | O_CLOEXEC);
	unlink(tmp_name);
	return (fd);
}

int	ms_open_infile(t_file *file)
{
	int	fd;

	while (file)
	{
		if (file->mode == MODE_READ)
			fd = open(file->filename, O_RDONLY | O_CLOEXEC);
		else if (file->mode == MODE_HEREDOC)
			fd = ms_heredoc(file);
		if (fd == -1)
		{
			ms_print_error(NULL, file->filename,
				": No such file or directory\n", 0);
			ms_exit(1);
		}
		if (file->next)
			close(fd);
		file = file->next;
	}
	return (fd);
}
