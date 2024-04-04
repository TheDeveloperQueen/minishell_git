/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:41:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 15:32:00 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_manage_io(t_io_node *io_list, t_data *data, t_commands_array *cmds,
	int flag)
{
	int	error;

	error = 0;
	while (io_list && !error)
	{
		if (io_list->io_type == IO_OUT)
			error = ft_out(io_list, data, cmds, flag);
		else if (io_list->io_type == IO_IN)
			error = ft_in(io_list, data, cmds, flag);
		else if (io_list->io_type == IO_APPEND)
			error = ft_append(io_list, data, cmds, flag);
		else if (io_list->io_type == IO_HEREDOC)
		{
			do_dup2(io_list->fd, 0, data, cmds);
			close(io_list->fd);
		}
		io_list = io_list->next;
	}
	return (error);
}

int	process_io(t_command *cmd, t_data *data, t_commands_array *cmds, int flag)
{
	if (ft_manage_io(cmd->infiles, data, cmds, flag)
		|| ft_manage_io(cmd->outfiles, data, cmds, flag))
		return (1);
	return (0);
}
