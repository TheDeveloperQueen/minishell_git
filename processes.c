/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:38 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/19 10:27:48 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (WIFEXITED(data->status))
		data->exit_value = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->exit_value = WTERMSIG(data->status) + 128;
}
