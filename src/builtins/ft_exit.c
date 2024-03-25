/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:31:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/25 14:49:36 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_command *cmd, t_data *data)
{
	printf("exit\n");
	data->exit_value = 0;
	if (!cmd->args || !cmd->args->content)
		exit(data->exit_value);
	if (!ft_str_isdigit(cmd->args->content))
	{
		printf("ourShell: exit: %s: numeric argument required\n", (char *)cmd->args->content);
		data->exit_value = 255;
		exit(EXIT_FAILURE);
	}
	else if (ft_lstsize(cmd->args) > 1)
	{
		printf("ourShell: exit: too many arguments\n");
		data->exit_value = 1;
		exit(EXIT_FAILURE);
	}
	else
	{
		data->exit_value = ft_atoi(cmd->args->content);
		data->exit_value = (data->exit_value % 256);
		exit(data->exit_value);
	}
	return (0);
}
