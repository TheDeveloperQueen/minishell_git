/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:09 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/05 21:02:53 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("%s: export: \'%s\': not a valid identifier\n",
			data->shell_name, str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("%s: export: \'%s\': not a valid identifier\n",
				data->shell_name, str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	valid_value(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("%s: export: \'%s\': not a valid identifier\n",
				data->shell_name, str);
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
	t_list	*lst;

	if (!cmd->args)
	{
		print_env(data, "declare -x %s=\"%s\"\n", "declare -x %s\n");
		return (0);
	}
	lst = cmd->args;
	while (lst)
	{
		if (!valid_name(name_env(lst), data))
			return (1);
		if (!ft_strchr(lst->content, '='))
		{
			if (!check_dup_env(data, lst->content))
				lst_add_back(&data->envp,
					lst_add_new(ft_strdup(lst->content), NULL));
		}
		else
			update_envp_value(data, lst->content);
		lst = lst->next;
	}
	return (0);
}
