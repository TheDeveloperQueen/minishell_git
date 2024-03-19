/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:20:08 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 15:20:50 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *com)
{
	if (com->name_and_args)
		free(com->name_and_args);
	if (com->name_and_args_splt)
		free_array(com->name_and_args_splt);
	if (com->infiles)
		ft_clear_io_lst(&com->infiles);
	if (com->outfiles)
		ft_clear_io_lst(&com->outfiles);
	free(com);
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
