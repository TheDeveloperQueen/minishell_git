/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:31:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 09:37:29 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_error_num(t_command *cmd)
{
	printf("%s: exit: %s: numeric argument required\n", SHELL_NAME,
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
		exit_error_num(cmd);
	else if (ft_lstsize(cmd->args) > 1)
	{
		printf("%s: exit: too many arguments\n", SHELL_NAME);
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
