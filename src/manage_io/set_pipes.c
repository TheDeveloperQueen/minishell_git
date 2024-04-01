/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:56:23 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/01 11:42:18 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
void     check_pipe(t_command *cmd, t_commands_array *cmds_array, int index)
{
    if  (index == 0 && cmds_array->len > 1)
        cmd->pipe = PIPE_OUT;
    else if (index == 0)
        cmd->pipe = NO_PIPE;
    else if (index > 0 && index < cmds_array->len - 1)
        cmd->pipe = PIPE_IN_OUT;
    else if (index != 0 && index == cmds_array->len - 1)
        cmd->pipe = PIPE_IN;
}

static int do_pipe(int fd[2])
{
    int return_fd;
    
    return_fd = pipe(fd);
    if (return_fd == -1)
    {
        perror("pipe Error\n");
       exit(EXIT_FAILURE);
    }
    return (return_fd);
}

static int set_pipe_in(t_command *cmd)
{
	if (cmd->fd_in >= 0)
    {
        do_dup2(cmd->fd_in, STDIN_FILENO);
        close_file(cmd->fd_in);
    }
	else
	{
    	cmd->fd_in = cmd->pipe_fd[READ];
    	do_dup2(cmd->pipe_fd[READ], STDIN_FILENO);
		close_file(cmd->pipe_fd[READ]);
	}
    return (0);
}

static int set_pipe_out(t_command *cmd)
{
	if (cmd->fd_out >= 0)
    {
        do_dup2(cmd->fd_out, STDOUT_FILENO);
        close_file(cmd->fd_out);
    }
	else
	{
    	do_pipe(cmd->pipe_fd);
    	cmd->fd_out = cmd->pipe_fd[WRITE];
    	do_dup2(cmd->pipe_fd[WRITE], STDOUT_FILENO);
		close_file(cmd->pipe_fd[WRITE]);
	}
    return (0);
}

static int set_pipe_in_out(t_command *cmd)
{
	set_pipe_in(cmd);
	set_pipe_out(cmd);
    return (0);
}

int set_pipes(t_command *cmd)
{
    if (cmd->pipe == PIPE_IN)
        return (set_pipe_in(cmd));
    if (cmd->pipe == PIPE_OUT)
        return (set_pipe_out(cmd));
    if (cmd->pipe == PIPE_IN_OUT)
        return (set_pipe_in_out(cmd));
    return (0);
}
*/

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
