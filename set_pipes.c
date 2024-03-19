/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:56:23 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 13:01:08 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
        close_file(cmd->fd_in);
    do_dup2(cmd->pipe_fd[READ], STDIN_FILENO);
    cmd->fd_in = cmd->pipe_fd[READ];
    return (0);
}

static int set_pipe_out(t_command *cmd)
{
    if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
        close_file(cmd->fd_out);
    do_pipe(cmd->pipe_fd);
    do_dup2(cmd->pipe_fd[WRITE], STDOUT_FILENO);
    cmd->fd_out = cmd->pipe_fd[WRITE];
    return (0);
}

static int set_pipe_in_out(t_command *cmd)
{
    if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
        close_file(cmd->fd_in);
    if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
        close_file(cmd->fd_out);
    do_dup2(cmd->pipe_fd[READ], STDIN_FILENO);
    cmd->fd_in = cmd->pipe_fd[READ];
    do_pipe(cmd->pipe_fd);
    do_dup2(cmd->pipe_fd[WRITE], STDOUT_FILENO);
    cmd->fd_out = cmd->pipe_fd[WRITE];
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