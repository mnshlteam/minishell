/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:26:24 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 19:43:56 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export(char **strs)
{
	while (*strs)
	{
		if (!ms_export_error(*strs))
			ms_addenv(ft_strdup(*strs));
		strs++;
	}
}

void	ms_unset(char **strs)
{
	while (*strs)
	{
		if (!ms_unset_error(*strs))
			ms_delenv(*strs);
		strs++;
	}
}

void	ms_env(void)
{
	t_env	*tmp;

	tmp = g_config.env;
	while (tmp)
	{
		printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
}

char	*ms_findenv(char *str)
{
	t_env	*tmp;

	tmp = g_config.env;
	while (tmp)
	{
		if (ms_envmatch(tmp, str))
			return (tmp->env);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ms_getenv(char *str)
{
	char	*env;

	env = ms_findenv(str);
	if (env)
		return (ft_strchr(env, '=') + 1);
	return ("");
}
