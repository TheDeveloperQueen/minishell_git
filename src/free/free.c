/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:43:24 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 20:43:37 by ritavasques      ###   ########.fr       */
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

void	ft_delete_io_lst(t_io_node *lst)
{
	t_io_node	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->io_arg)
			free(lst->io_arg);
		free(lst);
		lst = temp;
	}
}

void	free_cmd(t_command *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->args_splitted)
		free_array(cmd->args_splitted);
	if (cmd->args)
		ft_delete_lst(cmd->args);
	if (cmd->infiles)
		ft_delete_io_lst(cmd->infiles);
	if (cmd->outfiles)
		ft_delete_io_lst(cmd->outfiles);
	if (cmd->name_and_args)
		free(cmd->name_and_args);
	if (cmd->name_and_args_splt)
		free_array(cmd->name_and_args_splt);
	free(cmd);
}

void	free_cmds_array(t_commands_array *cmds_array)
{
	int	i;

	i = 0;
	if (cmds_array)
	{
		while (cmds_array->comm_array[i])
		{
			free_cmd(cmds_array->comm_array[i]);
			i++;
		}
		free(cmds_array->comm_array);
		free(cmds_array);
	}
}
