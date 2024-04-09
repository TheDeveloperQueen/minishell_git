/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:00:00 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/09 13:16:24 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_stds(t_data *data, int piped)
{
	if (!piped)
	{
		do_dup2(data->stdin, STDIN_FILENO, data);
		do_dup2(data->stdout, STDOUT_FILENO, data);
	}
}

static int	exec_child(t_data *data, t_cmd *cmd)
{
	int		tmp_status;
	char	*path;
	char	**envp_str;
	char	**args;

	//g_minishell.signint_child = true;
	data->last_pid = fork();
	if (data->last_pid == 0)
	{
		tmp_status = process_io(cmd, data, 0);
		if (tmp_status != 0)
		{
			clear_shell(data);
			exit(tmp_status);
		}
		path = paths(data, cmd);
		tmp_status = check_path_access(path);
		if (tmp_status != 0)
		{
			clear_shell(data);
			exit(tmp_status);
		}
		envp_str = array_env(data->envp);
		args = cmd->name_and_args_splt;
		execve(path, args, envp_str);
		free(path);
		free_array(envp_str);
		perror(cmd->name);
		clear_shell(data);
		exit(EXIT_FAILURE);
	}
	waitpid(data->last_pid, &tmp_status, 0);
	//g_minishell.signint_child = false;
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_simple_cmd(t_data *data, t_cmd *cmd, int piped)
{
	int			tmp_status;

	if (!cmd->name_and_args)
	{
		tmp_status = process_io(cmd, data, 1);
		return (reset_stds(data, piped), tmp_status);
	}
	else if (is_builtin(cmd))
	{
		tmp_status = process_io(cmd, data, 1);
		if (tmp_status != 0)
			return (reset_stds(data, piped), tmp_status);
		tmp_status = exec_builtin(cmd, data);
		return (reset_stds(data, piped), tmp_status);
	}
	else
		return (exec_child(data, cmd));
}
