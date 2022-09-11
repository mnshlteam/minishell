/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:40:41 by yolee             #+#    #+#             */
/*   Updated: 2022/09/11 21:52:08 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_filename_join(char *filedir, char *filename)
{
	char	*temp_str;
	char	*result_str;

	temp_str = ft_strjoin(filedir, "/");
	result_str = ft_strjoin(temp_str, filename);
	if (!temp_str)
		free(temp_str);
	return (result_str);
}

static void	ms_execfile(char *filedir, char *filename, char **str)
{
	DIR				*dir;
	struct dirent	*ent;

	(void)filename;
	(void)str;
	dir = opendir(filedir);
	if (!dir)
		return ;
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (ft_strncmp(ent->d_name, filename, ft_strlen(filename)))
			execve(ms_filename_join(filedir, filename), str, NULL);
		printf("%s\n", ent->d_name);
	}
	closedir(dir);
}

void	ms_findpath(char *filename, char **str)
{
	char	*path;
	char	*iter;
	char	*iter_end;
	char	buf[1024];

	path = ms_getenv("PATH");
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
		printf("%s\n", buf);
		iter = iter_end + 1;
		ms_execfile(buf, filename, str);
	}
}
