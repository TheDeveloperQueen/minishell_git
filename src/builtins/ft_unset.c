/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:11 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/20 11:03:03 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_command *cmd, t_data *data)
{
	t_llist	*aux_envp;
	t_llist *temp;
	t_list	*names;

	aux_envp = data->envp;
	names = cmd->args;
	while (names)
	{
		temp = aux_envp;
		while (aux_envp)
		{
			if(ft_strncmp(aux_envp->name, (char *)names->content, ft_charfind((char *)names->content, '=')) == 0 || ft_strcmp(aux_envp->name, (char *)names->content) == 0)
			{
				llist_remove(&aux_envp);
				break;
				
			}
			aux_envp = aux_envp->next;
		}
		names = names->next;
		temp = aux_envp;
	}
	return (0);
}
