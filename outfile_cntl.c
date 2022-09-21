/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_cntl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:34:52 by yolee             #+#    #+#             */
/*   Updated: 2022/09/21 20:58:02 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fd_err_handle(t_file *file)
{
	struct stat	buf;

	if (stat(file->filename, &buf))
	{
		ms_print_error(NULL, NULL, strerror(errno), 0);
		ms_exit(EXIT_FAILURE);
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
		{
			ms_print_error(NULL, file->filename, ": is a directory", 0);
			ms_exit(EXIT_FAILURE);
		}
	}
}

int	ms_open_outfile(t_file *file)
{
	int			fd;

	while (file)
	{
		if (file->mode == MODE_WRITE)
			fd = open(file->filename, O_CREAT | O_WRONLY \
			| O_TRUNC | O_CLOEXEC, 0644);
		else if (file->mode == MODE_APPEND)
			fd = open(file->filename, O_CREAT | O_WRONLY \
			| O_APPEND | O_CLOEXEC, 0644);
		if (fd == -1)
			fd_err_handle(file);
		if (file->next)
			close(fd);
		file = file->next;
	}
	return (fd);
}
