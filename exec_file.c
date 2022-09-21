/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:21:00 by yolee             #+#    #+#             */
/*   Updated: 2022/09/21 20:55:34 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_file(char *filename, char **argv)
{
	struct stat	buf;

	if (stat(filename, &buf))
	{
		ms_print_error(NULL, filename, ": No such file or directory", 0);
		ms_exit(127);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ms_print_error(NULL, filename, ": is a directory", 0);
		ms_exit(126);
	}
	else
	{
		if (execve(filename, argv, g_config.envp))
		{
			ms_print_error(NULL, NULL, strerror(errno), 0);
			ms_exit(EXIT_FAILURE);
		}
	}
}
