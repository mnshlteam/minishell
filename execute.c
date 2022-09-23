/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:01:43 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 17:06:31 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_strisnum(char *str)
{
	int	i;

	i = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ms_exit_main(char **argv)
{
	printf("exit\n");
	if (!*argv)
		exit(0);
	if (*(argv + 1) && *(argv + 2))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_config.exit_status = 1;
		return ;
	}
	if (!ms_strisnum(*argv))
	{
		ms_print_error("exit: ", *argv, ": numeric argument required\n", 0);
		exit(255);
	}
	exit(ft_atoi(*argv));
}

int	ms_run_by_parent(char **strs)
{
	if (!ft_strncmp(*strs, "export", 7))
		return (1);
	if (!ft_strncmp(*strs, "unset", 6))
		return (1);
	if (!ft_strncmp(*strs, "cd", 3))
		return (1);
	if (!ft_strncmp(*strs, "exit", 5))
		return (1);
	return (0);
}

void	ms_run_parent(t_cmd *cmd, char **strs)
{
	if (cmd->next)
		return ;
	if (!ft_strncmp(*strs, "export", 7))
		ms_export(strs + 1);
	else if (!ft_strncmp(*strs, "unset", 6))
		ms_unset(strs + 1);
	else if (!ft_strncmp(*strs, "cd", 3))
		ms_cd(*(strs + 1));
	else
		ms_exit_main(strs + 1);
}

void	ms_execute(char **strs)
{
	if (!ft_strncmp(*strs, "echo", 5))
		ms_echo(strs + 1);
	else if (!ft_strncmp(*strs, "env", 4))
		ms_env();
	else if (!ft_strncmp(*strs, "pwd", 4))
		ms_pwd();
	else if (ft_strchr(*strs, '/'))
		ms_exec_file(*(strs), strs);
	else if (!(*strs)[0])
		return ;
	else
		ms_findpath(*(strs), strs);
	return ;
}
