/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:01:43 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 22:53:53 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execute(char **strs)
{
	if (!ft_strncmp(*strs, "echo", 5))
		ms_echo(strs + 1);
	else if (!ft_strncmp(*strs, "export", 7))
		ms_export(strs + 1);
	else if (!ft_strncmp(*strs, "unset", 6))
		ms_unset(strs + 1);
	else if (!ft_strncmp(*strs, "env", 4))
		ms_env();
	else if (!ft_strncmp(*strs, "pwd", 4))
		printf("%s\n", g_config.pwd);
	else if (!ft_strncmp(*strs, "exit", 5))
		ms_exit();
}
