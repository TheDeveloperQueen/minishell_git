/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:41:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/14 11:39:14 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_manage_io(t_io_node *io_list, t_data *data, int is_father)
{
	int	error;

	error = 0;
	while (io_list && !error)
	{
		if (io_list->io_type == IO_OUT)
			error = ft_out(io_list, data, is_father);
		else if (io_list->io_type == IO_IN)
			error = ft_in(io_list, data, is_father);
		else if (io_list->io_type == IO_APPEND)
			error = ft_append(io_list, data, is_father);
		else if (io_list->io_type == IO_HEREDOC)
		{
			do_dup2(io_list->fd, 0, data);
			close(io_list->fd);
		}
		io_list = io_list->next;
	}
	return (error);
}

int	process_io(t_cmd *cmd, t_data *data, int is_father)
{
	return (ft_manage_io(cmd->infiles, data, is_father)
		|| ft_manage_io(cmd->outfiles, data, is_father));
}
