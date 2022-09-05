/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:26:24 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 16:40:42 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export(char *str)
{
	ms_addenv(ft_strdup(str));
}

void	ms_unset(char *str)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*next;

	tmp = g_config.env;
	prev = NULL;
	while (tmp)
	{
		if (ms_envmatch(tmp, str))
		{
			next = tmp->next;
			free(tmp->env);
			free(tmp);
			if (prev)
				prev->next = next;
			else
				g_config.env = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
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
	return (NULL);
}
