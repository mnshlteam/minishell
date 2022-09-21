/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:26:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 17:37:42 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(pid_t pid)
{
	(void)pid;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_bs(pid_t pid)
{
	(void)pid;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
}

void	handle_proc_quit(pid_t pid)
{
	(void)pid;
	ms_envfree();
	exit(EXIT_SUCCESS);
}

void	ms_exit(char *str, int status)
{
	ms_envfree();
	if (str)
		printf("%s\n", str);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	if (argc > 1)
	{
		printf("minishell has no arguments\n");
		return (1);
	}
	ms_init(envp);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bs);
	signal(SIGTERM, handle_proc_quit);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms_free_cmd(ms_parse(line));
		free(line);
	}
	ms_exit(NULL, 0);
}
