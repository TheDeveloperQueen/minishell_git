/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:09 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/04 15:23:08 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("ourShell: export: \'%s\': not a valid identifier\n", str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("ourShell: export: \'%s\': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	valid_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("ourShell: export: \'%s\': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*name_env(t_list *lst)
{
	char	*name;

	name = ft_substr(lst->content, 0, ft_charfind(lst->content, '='));
	return (name);
}

int	ft_export(t_command *cmd, t_data *data)
{
	t_llist	*aux_envp;
	t_list	*lst;

	aux_envp = data->envp;
	if (!cmd->args)
	{
		print_env(data, "declare -x %s=\"%s\"\n", "declare -x %s\n");
		return (0);
	}
	lst = cmd->args;
	while (lst)
	{
		if (!valid_name(name_env(lst)))
			return (1);
		if (!ft_strchr(lst->content, '='))
		{
			if (!check_dup_env(data, lst->content))
				lst_add_back(&aux_envp,
					lst_add_new(ft_strdup(lst->content), NULL));
		}
		else
			update_envp_value(data, lst->content);
		lst = lst->next;
	}
	return (0);
}
