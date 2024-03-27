/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:38 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/27 17:12:33 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	child_process1(t_data *data, t_command *cmd)
{
	char	*path;
	char	**envp_str;
	char	**args;
	
	path = paths(data, cmd);
	envp_str = array_env(data->envp, "=");
	args = cmd->name_and_args_splt;
	
	pipe(cmd->pipe_fd);
	data->last_pid = fork();
	if (data->last_pid < 0)
		exit(EXIT_FAILURE);
	if (data->last_pid == 0)
	{
		execve(path, args, envp_str);
	free(path);
	free_array(envp_str);
	free_array(args);	
	perror(cmd->name);
	exit(EXIT_FAILURE);
	}
}*/

void	child_process(t_data *data, t_command *cmd)
{
	char	*path;
	char	**envp_str;
	char	**args;
	
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

void	parent_process(t_data *data)
{
	int	last_exc;
	int	status;

	last_exc = 0;
	while (last_exc != -1)
	{
		last_exc = waitpid(-1, &status, 0);
		if (last_exc == data->last_pid)
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
	}
}
