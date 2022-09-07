/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:30 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/07 17:03:27 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(char *str)
{
	if (chdir(str))
		printf("Error to change directory.\n");
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
