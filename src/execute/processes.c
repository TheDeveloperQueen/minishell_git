/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:38 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/22 20:23:15 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_data *data, t_command *cmd)
{
	char	*path;
	char	**envp_str;
	char	**args;
	
	path = paths(data, cmd);
	envp_str = array_env(data, "=");
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
