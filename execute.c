/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:30:16 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 13:06:17 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
        data->exit_value = ft_echo(cmd);
    if (ft_strcmp(cmd->name, "pwd") == 0)
        data->exit_value = ft_pwd(cmd);
    if (ft_strcmp(cmd->name, "cd") == 0)
        data->exit_value = ft_cd(cmd);
    if (ft_strcmp(cmd->name, "env") == 0)
        data->exit_value = ft_env(data->envp);
    if (ft_strcmp(cmd->name, "export") == 0)
        data->exit_value = ft_export(cmd, data);
	//if (ft_strcmp(cmd->name, "unset") == 0)
        //data->exit_value = ft_unset(cmd, data);
	if (ft_strcmp(cmd->name, "exit") == 0)
        data->exit_value = ft_exit(cmd, data);
	return (data->exit_value);
}

int	do_cmd(t_command *cmd, t_commands_array *cmds_array, t_data *data, t_io_node *fd, int index)
{
	check_pipe(cmd, cmds_array, index);
	set_files(cmd, fd, data);
	data->exit_value = 0;
	if (is_builtin(cmd) && cmd->pipe == NO_PIPE)
		data->status = exec_builtin(cmd, data);
	else if (check_envp(data, "PATH", NULL) != 0 || has_path(cmd) || is_builtin(cmd))
		full_execute(data, cmd);
	else
	{
		printf("%s: No such file or directory\n", cmd->name);
		exit(EXIT_FAILURE);
	}
	return (data->exit_value);
}

void    exec_cmd_lst(t_data *data, t_command *cmd, t_commands_array *cmds_array, t_io_node *fd)
{
    int i;
    
    i = 0;
    while(cmds_array->comm_array[i])
    {
        data->exit_value = do_cmd(cmd, cmds_array, data, fd, i);
        i++;
    }
    if (data->heredoc == 1)
        unlink("heredoc");
}

void    full_execute(t_data *data, t_command *cmd)
{
    pid_t   child;
    
    //signals_child();
    child = fork();
    if (child < 0)
        exit(EXIT_FAILURE);
    if (child == 0)
    {
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
    waitpid(child, &data->status, 0);
    //signals();
    parent_process(data);
}
