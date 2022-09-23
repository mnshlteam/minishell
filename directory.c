/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:30 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 17:34:05 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(char *str)
{
	struct stat	buf;

	if (chdir(str))
	{
		if (stat(str, &buf))
		{
			ms_print_error("cd: ", str, \
				": No such file or directory\n", 0);
			return ;
		}
		if (!S_ISDIR(buf.st_mode))
		{
			ms_print_error("cd: ", str, ": Not a directory\n", 0);
			g_config.exit_status = 1;
			return ;
		}
		g_config.exit_status = 1;
	}
	else
	{
		str = getcwd(NULL, 0);
		ms_addenv(ft_strjoin("PWD=", str));
		free(str);
	}
}

void	ms_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}
