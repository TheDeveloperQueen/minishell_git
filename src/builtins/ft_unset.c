/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:11 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/26 10:10:49 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_var(char *var_name, char *arg_name)
{
	if (ft_strcmp(var_name, arg_name) == 0
		&& ft_strlen(var_name) == ft_strlen(arg_name))
		return (1);
	return (0);
}

void	delete_var(t_llist **envp)
{
	t_llist	*start;

	if (!*envp)
		return ;
	start = *envp;
	*envp = start->next;
	if (start->name)
		free(start->name);
	if (start->value)
		free(start->value);
	free(start);
	return ;
}

void	unset_var(char *var_name, t_llist **envp)
{
	t_llist	*curr;
	t_llist	*tmp;

	curr = *envp;
	while (curr)
	{
		if (is_var(curr->name, var_name))
		{
			if (curr == *envp)
				return (delete_var(envp));
			else
			{
				tmp = *envp;
				while (curr != tmp->next)
					tmp = tmp->next;
				return (delete_var(&tmp->next));
			}
		}
		curr = curr->next;
	}
}

int	ft_unset(t_command *cmd, t_data *data)
{
	t_list	*args;

	args = cmd->args;
	while (args)
	{
		unset_var(args->content, &data->envp);
		args = args->next;
	}
	return (0);
}
