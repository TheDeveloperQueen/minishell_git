/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:09 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 14:51:50 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_msg(char *name_and_vaule)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(SHELL_NAME, ": export: '");
	str2 = ft_strjoin(str1, name_and_vaule);
	free(str1);
	str1 = ft_strjoin(str2, "': not a valid identifier\n");
	free(str2);
	ft_putstr_fd(str1, STDERR_FILENO);
}

int	valid_name(char *name, char *name_and_value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		print_error_msg(name_and_value);
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			print_error_msg(name_and_value);
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

int	ft_export(t_cmd *cmd, t_data *data)
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
		if (!valid_name(name_env(lst), lst->content))
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
