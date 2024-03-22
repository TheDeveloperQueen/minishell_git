/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:11 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 12:09:05 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_command *cmd, t_data *data)
{
	t_llist	*aux_envp;
	t_list	*names;

	aux_envp = data->envp;
	names = cmd->args;
	if (names)
	{
		while (names)
		{
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
		}
	}
	return (0);
}
