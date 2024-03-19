/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:43:24 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/18 20:07:40 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;

	i = 0;
	free(cmd->name);
	while (cmd->args_splitted[i])
	{
		free(cmd->args_splitted[i]);
		i++;
	}
	if (cmd->args)
		ft_delete_lst(cmd->args);
	if (cmd->infiles)
		ft_delete_io_lst(cmd->infiles);
	if (cmd->outfiles)
		ft_delete_io_lst(cmd->outfiles);
	free(cmd);
}

void	exit_shell(t_data *data, t_command *cmd)
{
	int		error;

	error = data->exit_value;
	free_cmd(cmd);
	free(data);
	if (error)
		exit(error);
	exit(EXIT_SUCCESS);
}
