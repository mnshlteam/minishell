/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:25:48 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/04 19:19:18 by hyejo            ###   ########.fr       */
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

t_config	*g_config;

void	ms_addenv(char *str);

#endif
