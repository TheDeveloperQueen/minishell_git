/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files22.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:07:49 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/01 11:34:04 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_file(int fd)
{
	int	return_fd;

	return_fd = close(fd);
	if (return_fd == -1)
	{
		perror("close Error\n");
		exit(EXIT_FAILURE);
	}
	return (return_fd);
}

/* int	set_files(t_command *cmd)
{
	get_fd_in(cmd);
	get_fd_out(cmd);
	if (cmd->pipe && cmd->pipe != NO_PIPE)
		set_pipes(cmd);
	return (0);
} */
