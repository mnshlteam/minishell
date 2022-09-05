/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctrl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:16:00 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 22:20:47 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init(char **envp)
{
	t_env	*env;
	t_env	*tmp;

	g_config.pwd = getcwd(g_config.pwd, 0);
	while (*envp)
	{
		env = malloc(sizeof(t_env));
		env->env = ft_strdup(*envp);
		env->next = NULL;
		if (!g_config.env)
			g_config.env = env;
		else
		{
			tmp = g_config.env;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = env;
		}
		envp++;
	}
}

int	ms_envmatch(t_env *env, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (env->env[i] && env->env[i] != '=')
		i++;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (i != j || ft_strncmp(env->env, str, i) != 0)
		return (0);
	return (1);
}

void	ms_addenv(char *str)
{
	t_env	*tmp;
	t_env	*env;

	tmp = g_config.env;
	while (1)
	{
		if (ms_envmatch(tmp, str))
		{
			free(tmp->env);
			tmp->env = str;
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env->env = str;
	env->next = 0;
	tmp->next = env;
}

void	ms_delenv(char *str)
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
			return ;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	ms_envfree(void)
{
	t_env	*tmp;
	t_env	*next;

	tmp = g_config.env;
	g_config.env = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->env);
		free(tmp);
		tmp = next;
	}
	free(g_config.pwd);
}
