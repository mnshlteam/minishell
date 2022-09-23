/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:30 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 15:39:08 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(char *str)
{
	if (chdir(str))
	{
		ms_print_error("cd: ", str, \
			": No such file or directory", ft_strlen(str));
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
