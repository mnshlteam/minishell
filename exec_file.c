/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:21:00 by yolee             #+#    #+#             */
/*   Updated: 2022/09/20 18:35:38 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_file(char *filename, char **argv)
{
	struct stat	buf;

	if (stat(filename, &buf))
		ms_exit("minishell: (filename): No such file or directory", 127);
	else if (S_ISDIR(buf.st_mode))
		ms_exit("minishell: (filename): is a directory", 126);
	else
	{
		if (execve(filename, argv, g_config.envp))
			ms_exit("custom error message", EXIT_FAILURE);
	}
}
