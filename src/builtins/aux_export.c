/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:50:39 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/11 14:56:23 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dup_env(t_data *data, char *name)
{
	t_llist	*aux_envp;

	aux_envp = data->envp;
	while (aux_envp)
	{
		if (ft_strncmp(aux_envp->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(aux_envp->name))
			return (1);
		aux_envp = aux_envp->next;
	}
	return (0);
}

void	replace_env(t_data *data, char *name, char *n_value)
{
	t_llist	*aux_envp;

	aux_envp = data->envp;
	while (aux_envp)
	{
		if (ft_strncmp(aux_envp->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(aux_envp->name))
		{
			if (aux_envp->value)
				free(aux_envp->value);
			aux_envp->value = n_value;
			return ;
		}
		aux_envp = aux_envp->next;
	}
}

void	update_envp_value(t_data *data, char *argument)
{
	char	*name;
	char	*value;

	name = ft_substr(argument, 0, ft_charfind(argument, '='));
	if (argument[ft_strlen(argument - 1)] == '=')
		value = ft_strdup("");
	else
		value = ft_substr(argument, ft_charfind(argument, '=') + 1,
				ft_strlen(argument));
	if (!check_dup_env(data, name))
	{
		lst_add_back(&data->envp, lst_add_new(name, value));
	}
	else
	{
		replace_env(data, name, value);
		free(name);
	}
}
