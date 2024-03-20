/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:07:49 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/20 15:39:49 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	set_files(t_command *cmd)
{
    if (cmd->pipe && cmd->pipe != NO_PIPE)
		set_pipes(cmd);
	get_fd_in(cmd);
    get_fd_out(cmd);
    if (cmd->fd_in >= 0)
    {
        do_dup2(cmd->fd_in, STDIN_FILENO);
        close_file(cmd->fd_in);
    }
    if (cmd->fd_out >= 0)
    {
        do_dup2(cmd->fd_out, STDOUT_FILENO);
        close_file(cmd->fd_out);
    }
	return (0);
}