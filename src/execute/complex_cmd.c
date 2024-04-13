/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:32:29 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/13 13:41:44 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_pipe_right( t_data *data, int index, int pfds[2])
{
	int	status;

	close(pfds[1]);
	do_dup2(pfds[0], STDIN_FILENO, data);
	close(pfds[0]);
	status = ft_exec_cmds(data, index, 1);
	clear_shell(data);
	exit(status);
}

static void	ft_exec_pipe_left(t_data *data, t_cmd *cmd, int pfds[2])
{
	int	status;

	close(pfds[0]);
	do_dup2(pfds[1], STDOUT_FILENO, data);
	close(pfds[1]);
	status = ft_exec_simple_cmd(data, cmd, 1);
	clear_shell(data);
	exit(status);
}

static	int	ft_exec_pipeline(t_data *data, int index)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	set_child_signals_handlers();
	data->status = 0;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_left(data, data->cmds->array[index], pfds);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_right(data, index + 1, pfds);
		else
		{
			(close(pfds[0]), close(pfds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			set_father_signals_handlers();
			return (WEXITSTATUS(status));
		}
	}
	return (1);
}

int	ft_exec_cmds(t_data *data, int index, int piped)
{
	if (!data->cmds)
		return (1);
	if (index < data->cmds->len - 1)
		return (ft_exec_pipeline(data, index));
	else
		return (ft_exec_simple_cmd(data, data->cmds->array[index], piped));
	return (1);
}
