/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:20:08 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/25 12:38:36 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_command *cmd)
{
	if (cmd->args)
		ft_delete_lst(cmd->args);
	if (cmd->name_and_args)
		free(cmd->name_and_args);
	if (cmd->name_and_args_splt)
		free_array(cmd->name_and_args_splt);
	if (cmd->infiles)
		ft_clear_io_lst(&cmd->infiles);
	if (cmd->outfiles)
		ft_clear_io_lst(&cmd->outfiles);
	free(cmd);
}

void	free_commands_array(t_commands_array *commands)
{
	int	i;

	i = 0;
	while (i < commands->len)
	{
		if (commands->comm_array[i])
			free_command(commands->comm_array[i]);
		i++;
	}
	free(commands->comm_array);
	free(commands);
}
