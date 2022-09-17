/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:25:48 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/16 19:44:08 by hyejo            ###   ########.fr       */
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

typedef struct s_file
{
	char			*filename;
	int				mode;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			*str;
	char			**cmd;
	t_file			*infile;
	t_file			*outfile;
	int				index;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_config
{
	char	**envp;
	t_env	*env;
	int		exit_status;
	int		fd[2][2];
}	t_config;

t_config	g_config;

void	ms_exit(char *str, int status);

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

void	ms_cd(char *str);
void	ms_pwd(void);

int		ms_isspace(char ch);
char	*ms_strjoin_free(char *s1, char *s2);
char	*str_to_env(char *str);
char	*ms_join_words(char **words);
void	free_strlist(char **strlist);

t_cmd	*ms_parse(char *line);

void	ms_add_last_file(t_cmd *cmd, char *fillename, int mode, int io);
void	ms_free_cmd(t_cmd *cmd);
t_cmd	*ms_new_cmd(t_cmd *prev);
int		ms_quote_status(char ch, int quote);

char	**ms_split_str(char *str);

char	*ms_parse_dollar(char *cmd, int quote);

char	*ms_parse_quotes(char *str);

char	*ms_parse_redirect(t_cmd *cmd, char *line, int quote);

#endif
