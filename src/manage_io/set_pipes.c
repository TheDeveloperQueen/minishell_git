/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:56:23 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/27 09:44:36 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_cmds_pipe_types(t_commands_array *cmds_array)
{
	int			i;
	t_command	*cmd;

	i = 0;
	while (i < cmds_array->len)
	{
		cmd = cmds_array->comm_array[i];
		if (i == 0 && cmds_array->len > 1)
			cmd->pipe = PIPE_OUT;
		else if (i == 0)
			cmd->pipe = NO_PIPE;
		else if (i > 0 && i < cmds_array->len - 1)
			cmd->pipe = PIPE_IN_OUT;
		else if (i != 0 && i == cmds_array->len - 1)
			cmd->pipe = PIPE_IN;
		i++;
	}
}

// static int	do_pipe(int fd[2])
// {
// 	int	return_fd;

// 	return_fd = pipe(fd);
// 	if (return_fd == -1)
// 	{
// 		perror("pipe Error\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (return_fd);
// }

static int	set_pipe_in(t_command **cmds, int i)
{
	t_command	*cmd;

	cmd = cmds[i];
	dup2(cmd->fd_in, STDIN_FILENO);
	close (cmd->fd_in);
	return (0);
}

static int	set_pipe_out(t_command **cmds, int i)
{
	int			pipe_fd[2];
	t_command	*next_cmd;

	next_cmd = cmds[i + 1];
	pipe(pipe_fd);
	next_cmd->fd_in = pipe_fd[READ];
	dup2(pipe_fd[1], STDOUT_FILENO);
	close (pipe_fd[1]);
	return (0);
}

static int	set_pipe_in_out(t_command **cmds, int i)
{
	int			pipe_fd[2];
	t_command	*cmd;
	t_command	*next_cmd;

	cmd = cmds[i];
	next_cmd = cmds[i + 1];
	dup2(cmd->fd_in, STDIN_FILENO);
	close (cmd->fd_in);
	pipe(pipe_fd);
	next_cmd->fd_in = pipe_fd[READ];
	dup2(pipe_fd[1], STDOUT_FILENO);
	close (pipe_fd[1]);
	return (0);
}

int	set_pipes(t_command **cmds, int i)
{
	t_command	*cmd;

	cmd = cmds[i];
	if (cmd->pipe == PIPE_IN)
		set_pipe_in(cmds, i);
	else if (cmd->pipe == PIPE_OUT)
		set_pipe_out(cmds, i);
	else if (cmd->pipe == PIPE_IN_OUT)
		set_pipe_in_out(cmds, i);
	return (0);
}
