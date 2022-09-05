/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:38:40 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 22:12:03 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 임시 파싱 함수

#include "minishell.h"

void	tmp_parse(char *line)
{
	char	**cmds;

	while (*line == ' ' || *line == '\t' || *line == '\r'
		|| *line == '\v' || *line == '\f')
		line++;
	if (!*line)
		return ;
	cmds = ft_split(line, ' ');
	ms_execute(cmds);
}
