/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:30:16 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/01 09:51:30 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_command *cmd, t_data *data)
{
	int exit_status;

	exit_status = 0;    
	if (ft_strcmp(cmd->name, "echo") == 0)
		exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
	   exit_status = ft_pwd(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		exit_status = ft_cd(data, cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		exit_status = ft_env(data);
	else if (ft_strcmp(cmd->name, "export") == 0)
		exit_status = ft_export(cmd, data);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		exit_status = ft_unset(cmd, data);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		exit_status = ft_exit(cmd, data);
	return (exit_status);
}

void	do_cmd(t_commands_array *cmds, t_data *data, int index)
{
	t_command	*cmd;

	cmd = cmds->comm_array[index];
	set_pipes(cmds->comm_array, index);
	get_args(cmd);
	if (is_builtin(cmd) && cmd->pipe == NO_PIPE)
	{
		process_io(cmd);
		data->status = exec_builtin(cmd, data);
	}
	else if (is_builtin(cmd) || has_path(cmd) || check_envp(data, "PATH", NULL) != 0)
		full_execute(data, cmd);
	else
	{
		printf("%s: No such file or directory\n", cmd->name);
		exit(EXIT_FAILURE);
	}
}

void	reset_stds(t_data *data)
{
	dup2(data->stdin, STDIN_FILENO);
	dup2(data->stdout, STDOUT_FILENO);
}

void	exec_cmd_lst(t_data *data, t_commands_array *cmds_array)
{
	int			i;

	i = 0;
	while (i < cmds_array->len)
	{
		do_cmd(cmds_array, data, i);
		reset_stds(data);
		i++;
	}
	parent_process(data);
}

void	full_execute(t_data *data, t_command *cmd)
{
	data->last_pid = fork();
	if (data->last_pid == 0)
	{
		process_io(cmd);
		if (is_builtin(cmd))
		{
			if (exec_builtin(cmd, data) == 0)
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		else
			child_process(data, cmd);
	}
	else if (data->last_pid < 0)
		exit(EXIT_FAILURE);
}
