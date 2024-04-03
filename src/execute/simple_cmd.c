/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:00:00 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/03 12:01:38 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_stds(t_data *data, int piped)
{
	if (!piped)
	{
		do_dup2(data->stdin, STDIN_FILENO);
		do_dup2(data->stdout, STDOUT_FILENO);
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
		free(path);
		free_array(envp_str);
		free_array(args);	
		perror(cmd->name);
		exit(EXIT_FAILURE);	
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
