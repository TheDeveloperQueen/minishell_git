/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:31:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/05 20:57:28 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_error_num(t_command *cmd, t_data *data)
{
	printf("%s: exit: %s: numeric argument required\n", data->shell_name,
		(char *)cmd->args->content);
	data->exit_value = 255;
	exit(EXIT_FAILURE);
}

static void	exit_error_size(t_data *data)
{
	printf("%s: exit: too many arguments\n", data->shell_name);
	data->exit_value = 1;
	exit(EXIT_FAILURE);
}

int	ft_exit(t_command *cmd, t_data *data)
{
	printf("exit\n");
	data->exit_value = 0;
	if (!cmd->args || !cmd->args->content)
		exit(data->exit_value);
	if (!ft_str_isdigit(cmd->args->content))
		exit_error_num(cmd, data);
	else if (ft_lstsize(cmd->args) > 1)
	{
		if (!ft_str_isdigit(cmd->args->content))
			exit_error_size(data);
		else
		{
			printf("%s: exit: too many arguments\n", data->shell_name);
			return (1);
		}
	}
	else
	{
		data->exit_value = ft_atoi(cmd->args->content);
		data->exit_value = (data->exit_value % 256);
		exit(data->exit_value);
	}
	return (0);
}
