/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:27:41 by yolee             #+#    #+#             */
/*   Updated: 2022/09/23 17:12:10 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	safe_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = 0;
	}
}

static void	ms_close_pipe(t_cmd *cmd)
{
	if (cmd->index)
	{
		if (cmd->next)
			safe_close(&g_config.fd[1][FD_WR]);
		safe_close(&g_config.fd[0][FD_RD]);
	}
	else
	{
		if (cmd->next)
			safe_close(&g_config.fd[0][FD_WR]);
		if (cmd->prev)
			safe_close(&g_config.fd[1][FD_RD]);
	}
}

static void	connect_pipe(t_cmd *cmd, int *in_fd, int *out_fd)
{
	if (cmd->index)
	{
		if (cmd->next)
		{
			safe_close(&g_config.fd[1][FD_RD]);
			(*out_fd) = g_config.fd[1][FD_WR];
		}
		safe_close(&g_config.fd[0][FD_WR]);
		(*in_fd) = g_config.fd[0][FD_RD];
	}
	else
	{
		if (cmd->next)
		{
			safe_close(&g_config.fd[0][FD_RD]);
			(*out_fd) = g_config.fd[0][FD_WR];
		}
		if (cmd->prev)
		{
			safe_close(&g_config.fd[1][FD_WR]);
			(*in_fd) = g_config.fd[1][FD_RD];
		}
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
	if (out_fd != 0)
		dup2(out_fd, STDOUT_FILENO);
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	ms_execute(cmd->cmd);
	exit(EXIT_SUCCESS);
}

void	ms_execute_proc(t_cmd *cmd)
{
	pid_t	c_pid;
	int		status;

	while (cmd)
	{
		if (cmd->next)
			pipe(g_config.fd[cmd->index]);
		if (ms_run_by_parent(cmd->cmd))
		{
			if (g_config.fd[cmd->index][FD_WR] > 2)
				safe_close(&g_config.fd[cmd->index][FD_WR]);
			ms_run_parent(cmd, cmd->cmd);
		}
		else
		{
			c_pid = fork();
			if (c_pid == 0)
				ms_child_proc_act(cmd);
			else
				ms_close_pipe(cmd);
			waitpid(c_pid, &status, WUNTRACED);
			g_config.exit_status = (status >> 8) & 0x000000ff;
		}
		cmd = cmd->next;
	}
}
