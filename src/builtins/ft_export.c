/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:09 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/25 15:39:52 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("export: \'%s\': not a valid identifier\n", str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("export: \'%s\': not a valid identifier\n", str);
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
			printf("export: \'%s\': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*name_env(t_command *cmd)
{
	char	*name;
	t_list	*lst;
	
	lst = cmd->args;
	name = ft_substr(lst->content, 0, ft_charfind(lst->content, '='));
	return (name);
}

char	*value_env(t_command *cmd)
{
	char	*value;
	t_list	*lst;
	
	value = NULL;
	lst = cmd->args;
	if  (ft_strchr(lst->content, '='))
		value = ft_substr(lst->content, ft_charfind(lst->content, '=') + 1, ft_strlen(lst->content));
	return (value);
}

int    ft_export(t_command *cmd, t_data *data)
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
		if (!valid_name(name_env(cmd)))
			return (0);
		if (!ft_strchr(lst->content, '='))
		{
			if (!check_dup_env(data, lst->content))
				lst_add_back(&aux_envp, lst_add_new(ft_strdup(lst->content), NULL));
		}
		else
		{
			if (valid_value(value_env(cmd)))
				update_envp_value(data, lst->content);
			else
				return (0);
		}
		lst = lst->next;
	}
	return (0);
	}
