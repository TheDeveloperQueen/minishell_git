/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:30:16 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 20:26:16 by ritavasques      ###   ########.fr       */
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

void	do_cmd(t_command *cmd, t_commands_array *cmds_array, t_data *data, int index)
{
    get_args(cmd);
	check_pipe(cmd, cmds_array, index);
	set_files(cmd);
	if (is_builtin(cmd) && cmd->pipe == NO_PIPE)
		data->status = exec_builtin(cmd, data);
	else if (is_builtin(cmd) || has_path(cmd) || check_envp(data, "PATH", NULL) != 0)
		full_execute(data, cmd);
	else
	{
		printf("%s: No such file or directory\n", cmd->name);
		exit(EXIT_FAILURE);
	}
}

void    exec_cmd_lst(t_data *data, t_commands_array *cmds_array)
{
    int i;
    t_command *cmd;
    
    i = 0;
    while(cmds_array->comm_array[i])
    {
        cmd = cmds_array->comm_array[i];
        do_cmd(cmd, cmds_array, data, i);
        i++;
    }
    if (data->heredoc == 1)
        unlink("heredoc");
    parent_process(data);
}

void    full_execute(t_data *data, t_command *cmd)
{
    data->last_pid = fork();
    printf("%d\n", data->last_pid);
    if (data->last_pid == 0)
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
    else if (data->last_pid < 0)
        exit(EXIT_FAILURE);
}
