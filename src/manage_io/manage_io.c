/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:41:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/27 08:06:34 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_manage_io(t_io_node *io_list)
{
	int	error;

	error = 0;
	while (io_list && !error)
	{
		if (io_list->io_type == IO_OUT)
			error = ft_out(io_list);
		else if (io_list->io_type == IO_IN)
			error = ft_in(io_list);
		else if (io_list->io_type == IO_APPEND)
			error = ft_append(io_list);
		else if (io_list->io_type == IO_HEREDOC)
		{
			dup2(io_list->fd, 0);
			close(io_list->fd);
		}
		io_list = io_list->next;
	}
	return (error);
}

int	process_io(t_command *cmd)
{
	if (ft_manage_io(cmd->infiles) || ft_manage_io(cmd->outfiles))
		return (1);
	return (0);
}
