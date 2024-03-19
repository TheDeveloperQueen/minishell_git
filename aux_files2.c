/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:07:49 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 11:29:07 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 int	close_file(int fd)
 {
    int return_fd;

    return_fd = close(fd);
    if (return_fd == -1)
    {
        perror("close Error\n");
        exit(EXIT_FAILURE);
    }
    return (return_fd);
 }

int	set_files(t_command *cmd, t_io_node *fd, t_data *data)
{
    if (cmd->pipe && cmd->pipe != NO_PIPE)
		set_pipes(cmd);
	cmd->fd_in = get_fd_in(cmd, fd);
    cmd->fd_out = get_fd_out(cmd, fd, data);
    do_dup2(cmd->fd_in, STDIN_FILENO);
    close_file(cmd->fd_in);
    do_dup2(cmd->fd_out, STDOUT_FILENO);
    close_file(cmd->fd_out);
	return (0);
}