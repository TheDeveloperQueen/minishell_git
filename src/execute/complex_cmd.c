/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:32:29 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 11:32:02 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_pipe_right( t_data *data, t_commands_array *cmds,
		int index, int pfds[2])
{
	int	status;

	close(pfds[1]);
	do_dup2(pfds[0], STDIN_FILENO, data, cmds);
	close(pfds[0]);
	status = ft_exec_cmds(data, cmds, index, 1);
	clear_shell(data, cmds);
	exit(status);
}

static void	ft_exec_pipe_left(t_data *data, t_command *cmd, int pfds[2],
		t_commands_array *cmds)
{
	int	status;

	close(pfds[0]);
	do_dup2(pfds[1], STDOUT_FILENO, data, cmds);
	close(pfds[1]);
	status = ft_exec_simple_cmd(data, cmd, 1, cmds);
	clear_shell(data, cmds);
	exit(status);
}

static	int	ft_exec_pipeline(t_data *data, t_commands_array *cmds, int index)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	//g_minishell.signint_child = true;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_left(data, cmds->comm_array[index], pfds, cmds);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_right(data, cmds, index + 1, pfds);
		else
		{
			(close(pfds[0]), close(pfds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			//g_minishell.signint_child = false;
			return (WEXITSTATUS(status));
		}
	}
	return (1);
}

int	ft_exec_cmds(t_data *data, t_commands_array *cmds, int index, int piped)
{
	if (!cmds)
		return (1);
	if (index < cmds->len - 1)
		return (ft_exec_pipeline(data, cmds, index));
	else
		return (ft_exec_simple_cmd(data, cmds->comm_array[index], piped, cmds));
	return (1);
}
