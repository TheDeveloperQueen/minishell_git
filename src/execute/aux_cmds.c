/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:58:05 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/07 13:29:51 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//commands args in list

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0 || ft_strcmp(cmd->name, "cd") == 0
		|| ft_strcmp(cmd->name, "pwd") == 0
		|| ft_strcmp(cmd->name, "export") == 0
		|| ft_strcmp(cmd->name, "unset") == 0
		|| ft_strcmp(cmd->name, "env") == 0
		|| ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, t_data *data)
{
	int	exit_status;

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
