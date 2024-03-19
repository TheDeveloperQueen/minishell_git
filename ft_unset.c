/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:11 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 13:20:02 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, t_command *cmd)
{
	t_list	*temp;

	temp = cmd->args;
	while (data->envp)
	{
		while (cmd->args)
		if (ft_strcmp(data->envp->name, cmd->args->content) == 0)
		{
			llist_remove(&data->envp);
			cmd->args = cmd->args->next;	
		}
		cmd->args = temp;
		data->envp = data->envp->name;
	}
	return (0);
}
