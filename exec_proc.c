/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:27:41 by yolee             #+#    #+#             */
/*   Updated: 2022/09/21 15:33:14 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_init_pipe(int cmd_idx)
{
	int	init_flag;

	init_flag = cmd_idx % 2;
	pipe(g_config.fd[init_flag]);
}

static void	ms_close_pipe(t_cmd *cmd)
{
	if (cmd->index % 2)
	{
		if (cmd->next && g_config.fd[0][FD_WR] > 2)
			close(g_config.fd[0][FD_WR]);
		if (cmd->index != 0 && g_config.fd[1][FD_RD] > 2)
			close(g_config.fd[1][FD_RD]);
	}
	else
	{
		if (cmd->next && g_config.fd[1][FD_WR] > 2)
			close(g_config.fd[1][FD_WR]);
		if (g_config.fd[0][FD_RD] > 2)
			close(g_config.fd[0][FD_RD]);
	}
}

static void	connect_pipe(t_cmd *cmd, int *in_fd, int *out_fd)
{
	if (cmd->index % 2)
	{
		if (cmd->next)
			(*out_fd) = g_config.fd[1][FD_WR];
		(*in_fd) = g_config.fd[0][FD_RD];
	}
	else
	{
		if (cmd->next)
			(*out_fd) = g_config.fd[0][FD_WR];
		if (cmd->prev)
			(*in_fd) = g_config.fd[1][FD_RD];
	}
}

static void	ms_child_proc_act(t_cmd *cmd)
{
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 0;
	connect_pipe(cmd, &in_fd, &out_fd);
	if (cmd->infile)
		in_fd = ms_open_infile(cmd->infile);
	if (cmd->outfile)
		out_fd = ms_open_outfile(cmd->outfile);
	dup2(out_fd, STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
	ms_execute(cmd->cmd);
	exit(EXIT_SUCCESS);
}

void	ms_execute_proc(t_cmd *cmd)
{
	pid_t	c_pid;

	while (cmd)
	{
		if (cmd->next)
			ms_init_pipe(cmd->index);
		c_pid = fork();
		if (c_pid == 0)
			ms_child_proc_act(cmd);
		else
			ms_close_pipe(cmd);
		waitpid(c_pid, &g_config.exit_status, WUNTRACED);
		cmd = cmd->next;
	}
}
