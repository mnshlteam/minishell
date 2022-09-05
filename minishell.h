/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:25:48 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 22:18:05 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_config
{
	t_env	*env;
	char	*pwd;
}	t_config;

t_config	g_config;

void	ms_exit(void);

void	ms_init(char **envp);
int		ms_envmatch(t_env *env, char *str);
void	ms_addenv(char *str);
void	ms_delenv(char *str);
void	ms_envfree(void);

void	ms_export(char **str);
void	ms_unset(char **str);
void	ms_env(void);
char	*ms_getenv(char *str);
char	*ms_findenv(char *str);

void	ms_echo(char **strs);

void	ms_execute(char **strs);

#endif
