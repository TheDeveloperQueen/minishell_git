/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:50:39 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 16:18:07 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dup_env(t_data *data, char *name)
{
	while (data->envp)
	{
		if (ft_strncmp((char *)data->envp->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen((char *)data->envp->name))
			return (1);
		data->envp = data->envp->next;
	}
	return (0);
}

void	*replace_env(t_data *data, char *name, char *n_value)
{
	while (data->envp)
	{
		if (check_dup_env(data, name))
		{
			if (data->envp->value)
				free(data->envp->value);
			data->envp->value = n_value;
			return (data->envp->value);
		}
		data->envp = data->envp->next;
	}
	return (NULL);
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
