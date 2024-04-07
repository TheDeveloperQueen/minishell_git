/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:43:24 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/07 13:54:07 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->envp)
		ft_delete_llst(data->envp);
	free(data);
}

void	free_command(t_command *cmd)
{
	if (cmd->name_and_args)
		ft_delete_lst(cmd->name_and_args);
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

void	clear_shell(t_data *data, t_commands_array *commands)
{
	if (commands)
		free_commands_array(commands);
	if (data)
		free_data(data);
}
