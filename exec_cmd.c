/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:40:41 by yolee             #+#    #+#             */
/*   Updated: 2022/09/22 16:01:17 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cmd_join(char *cmd_dir, char *cmd)
{
	char	*temp_str;
	char	*result_str;

	temp_str = ft_strjoin(cmd_dir, "/");
	result_str = ft_strjoin(temp_str, cmd);
	if (!temp_str)
		free(temp_str);
	return (result_str);
}

static void	ms_exec_cmd(char *cmd_dir, char *cmd, char **str)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(cmd_dir);
	if (!dir)
		return ;
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (ft_strncmp(ent->d_name, cmd, ft_strlen(cmd)))
			execve(ms_cmd_join(cmd_dir, cmd), str, NULL);
	}
	closedir(dir);
}

static void	ms_exec_cmd_pwd(char *cmd, char **str)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*pwd;

	pwd = getcwd(NULL, 0);
	dir = opendir(pwd);
	if (!dir)
		return ;
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (ft_strncmp(ent->d_name, cmd, ft_strlen(cmd)))
		{
			if (execve(ms_cmd_join(pwd, cmd), str, NULL))
			{
				ms_print_error(NULL, NULL, strerror(errno), 0);
				ms_exit(EXIT_FAILURE);
			}
		}
	}
	free(pwd);
	closedir(dir);
}

void	ms_findpath(char *cmd, char **str)
{
	char	*path;
	char	*iter;
	char	*iter_end;
	char	buf[1024];

	buf[0] = '\0';
	path = ms_getenv("PATH");
	if (!ft_strlen(path))
		ms_exec_cmd_pwd(cmd, str);
	iter = path;
	while (1)
	{
		iter_end = ft_strchr(iter, ':');
		if (!iter_end)
			iter_end = ft_strchr(iter, '\0');
		ft_strlcpy(buf, iter, iter_end - iter + 1);
		buf[iter_end - iter] = '\0';
		if (!buf[0])
			break ;
		iter = iter_end + 1;
		ms_exec_cmd(buf, cmd, str);
	}
	ms_print_error(NULL, cmd, ": command not found\n", 0);
	ms_exit(127);
}
