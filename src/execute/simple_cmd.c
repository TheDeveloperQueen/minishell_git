/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:00:00 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/07 16:36:30 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_stds(t_data *data, int piped, t_commands_array *cmds)
{
	if (!piped)
	{
		do_dup2(data->stdin, STDIN_FILENO, data, cmds);
		do_dup2(data->stdout, STDOUT_FILENO, data, cmds);
	}
}

static int	exec_child(t_data *data, t_command *cmd, t_commands_array *cmds)
{
	int		tmp_status;
	char	*path;
	char	**envp_str;
	char	**args;

	//g_minishell.signint_child = true;
	data->last_pid = fork();
	if (data->last_pid == 0)
	{
		tmp_status = process_io(cmd, data, cmds, 0);
		if (tmp_status != 0)
		{
			clear_shell(data, cmds);
			exit(EXIT_FAILURE);
		}
		path = paths(data, cmd);
		envp_str = array_env(data->envp);
		args = cmd->name_and_args_splt;
		execve(path, args, envp_str);
		free(path);
		free_array(envp_str);
		perror(cmd->name);
		clear_shell(data, cmds);
		exit(EXIT_FAILURE);
	}
	waitpid(data->last_pid, &tmp_status, 0);
	//g_minishell.signint_child = false;
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_simple_cmd(t_data *data, t_command *cmd, int piped,
		t_commands_array *cmds)
{
	int		tmp_status;

	if (!cmd->name_and_args)
	{
		tmp_status = process_io(cmd, data, cmds, 1);
		return (reset_stds(data, piped, cmds), tmp_status);
	}
	else if (is_builtin(cmd))
	{
		tmp_status = process_io(cmd, data, cmds, 1);
		if (tmp_status != 0)
			return (reset_stds(data, piped, cmds), tmp_status);
		tmp_status = exec_builtin(cmd, data);
		return (reset_stds(data, piped, cmds), tmp_status);
	}
	else
		return (exec_child(data, cmd, cmds));
}
