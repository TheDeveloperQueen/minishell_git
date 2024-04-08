/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:31:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/08 16:38:44 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_error_num(t_command *cmd, t_data *data)
{
	printf("%s: exit: %s: numeric argument required\n", data->shell_name,
		(char *)cmd->args->content);
	exit(2);
}

int	ft_exit(t_command *cmd, t_data *data)
{
	int	exit_value;

	printf("exit\n");
	if (!cmd->args || !cmd->args->content)
		exit(data->status);
	if (!ft_str_isdigit(cmd->args->content))
		exit_error_num(cmd, data);
	else if (ft_lstsize(cmd->args) > 1)
	{
		printf("%s: exit: too many arguments\n", data->shell_name);
		return (1);
	}
	else
	{
		exit_value = ft_atoi(cmd->args->content);
		exit_value = (exit_value % 256);
		exit(exit_value);
	}
	return (0);
}
