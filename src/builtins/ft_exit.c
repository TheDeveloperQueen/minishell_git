/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:31:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/12 14:11:25 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_num(char *arg)
{
	char	*str1;

	str1 = ft_strjoin("exit: ", arg);
	print_error_msg(str1, "numeric argument required");
	free(str1);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int		exit_value;

	exit_value = data->status;
	if (data->cmds->len == 1)
		printf("exit\n");
	if (!cmd->args || !cmd->args->content)
		exit((clear_shell(data), exit_value));
	if (!ft_str_isdigit(cmd->args->content))
		exit((print_error_num(cmd->args->content), clear_shell(data), 255));
	else if (ft_lstsize(cmd->args) > 1)
	{
		print_error_msg("exit", "too many arguments");
		return (1);
	}
	else
	{
		exit_value = ft_atoi(cmd->args->content);
		exit_value = (exit_value % 256);
		clear_shell(data);
		exit(exit_value);
	}
	return (0);
}
