/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:00:00 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/01 18:59:43 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_stds(t_data *data, int piped)
{
	if (!piped)
	{
		dup2(data->stdin, STDIN_FILENO);
		dup2(data->stdout, STDOUT_FILENO);
	}
}

static int	exec_child(t_data *data, t_command *cmd)
{
	int		tmp_status;
	char	*path;
	char	**envp_str;
	char	**args;

	//g_minishell.signint_child = true;
	data->last_pid = fork();
	if (data->last_pid == 0)
	{
		tmp_status = process_io(cmd);
		if (tmp_status != 0)
		{
			//(ft_clean_ms(), exit(ENO_GENERAL));
			exit(EXIT_FAILURE);
		}
		path = paths(data, cmd);
		envp_str = array_env(data->envp, "=");
		args = cmd->name_and_args_splt;
		execve(path, args, envp_str);
		//path_status = ft_get_path((node -> expanded_args)[0]);
		// if (path_status.err.no != ENO_SUCCESS)
		// {
		// 	tmp_status = ft_err_msg(path_status.err);
		// 	(ft_clean_ms(), exit(tmp_status));
		// }
		// if (execve(path_status.path, node -> expanded_args,
		// 		g_minishell.environ) == -1)
		// 	(ft_clean_ms(), exit(1));
	}
	waitpid(data->last_pid, &tmp_status, 0);
	//g_minishell.signint_child = false;
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_simple_cmd(t_data *data, t_command *cmd, int piped)
{
	int		tmp_status;

	if (!cmd->name_and_args)
	{
		tmp_status = process_io(cmd);
		return (reset_stds(data, piped), tmp_status);
	}
	else if (is_builtin(cmd))
	{
		get_args(cmd);
		tmp_status = process_io(cmd);
		if (tmp_status != 0)
			return (reset_stds(data, piped), 1);
		tmp_status = exec_builtin(cmd, data);
		return (reset_stds(data, piped), tmp_status);
	}
	else
		return (exec_child(data, cmd));
}
