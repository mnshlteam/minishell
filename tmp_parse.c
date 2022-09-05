/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:38:40 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 18:27:53 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 임시 파싱 함수

#include "minishell.h"

void	tmp_parse(char *line)
{
	char	**cmd;
	int		i;

	while (*line == ' ' || *line == '\t' || *line == '\r'
		|| *line == '\v' || *line == '\f')
		line++;
	if (!*line)
		return ;
	cmd = ft_split(line, ' ');
	i = 1;
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		while (cmd[i])
			ms_export(cmd[i++]);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		while (cmd[i])
			ms_unset(cmd[i++]);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ms_env();
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ms_exit();
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		printf("%s\n", g_config.pwd);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ms_echo(cmd + 1);
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}
