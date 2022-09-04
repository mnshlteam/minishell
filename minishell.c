/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:26:38 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/04 17:07:10 by hyejo            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*tmp;

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bs);
	while (1)
	{
		line = readline("minishell$ ");
		tmp = line;
		if (!tmp)
			break ;
		while (*tmp == ' ' || *tmp == '\t' || *tmp == '\r')
			tmp++;
		if (*tmp)
		{
			add_history(tmp);
		}
		free(line);
	}
	printf("exit\n");
}
