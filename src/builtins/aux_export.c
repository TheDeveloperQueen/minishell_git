/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:50:39 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 18:40:07 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dup_env(t_llist *lst, char *name)
{
	while (lst)
	{
		if (ft_strncmp((char *)lst->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(lst->name))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	*replace_env(t_llist *lst, char *name, char *n_value)
{
	while (lst)
	{
		if (check_dup_env(lst, name))
		{
			if (lst->value)
				free(lst->value);
			lst->value = n_value;
			return (lst->value);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	update_envp_value(t_llist *envp, char *argument)
{
	char	*name;
	char	*value;

	name = ft_substr(argument, 0, ft_charfind(argument, '='));
	if (argument[ft_strlen(argument - 1)] == '=')
		value = ft_strdup("");
	else
		value = ft_substr(argument, ft_charfind(argument, '=') + 1,
		ft_strlen(argument));
	if (!check_dup_env(envp, name))
	{
		lst_add_back(&envp, lst_add_new(name, value));
	}
	else
	{
		replace_env(envp, name, value);
		free(name);
	}
}
