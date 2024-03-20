/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:38 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/20 11:26:47 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_data *data, t_command *cmd)
{
	char	*path;
	char	**envp_str;
	char	**args;
	
	//signals_child();
	path = paths(data, cmd);
	envp_str = array_env(data->envp, "=");
	args = get_array_cmds(cmd);
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
