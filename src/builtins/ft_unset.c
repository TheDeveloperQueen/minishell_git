/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:11 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/25 16:58:52 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_command *cmd, t_data *data)
{
	t_llist	*curr;
	t_list	*names;
	t_llist	*prev;

	names = cmd->args;
	while (names)
	{
		prev = data->envp;
		if (ft_strncmp(prev->name, (char *)names->content, ft_charfind((char *)names->content, '=')) == 0 || ft_strcmp(prev->name, (char *)names->content) == 0)
		{
			data->envp = data->envp->next;
			free(data->envp->name);
			if (data->envp->value)
				free(data->envp->value);
			continue ;
		}
		curr = prev->next;
		while (curr)
		{
			if (ft_strncmp(curr->name, (char *)names->content, ft_charfind((char *)names->content, '=')) == 0 || ft_strcmp(curr->name, (char *)names->content) == 0)
			{
				prev->next = curr->next;
				free(curr->name);
				if (curr->value)
				free(curr->value);
				break ;
			}
			curr = curr->next;
		}
		names = names->next;
	}
	return (0);
}
