/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:09 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/11 20:47:08 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char *name, char *name_and_value)
{
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strjoin("export: ", name_and_value);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		print_error_msg(str_tmp, "not a valid identifier");
		return (free(str_tmp), 0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			print_error_msg(str_tmp, "not a valid identifier");
			return (free(str_tmp), 0);
		}
		i++;
	}
	free(str_tmp);
	return (1);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	t_list	*lst;
	char	*name;

	if (!cmd->args)
	{
		print_env(data, "declare -x %s=\"%s\"\n", "declare -x %s\n");
		return (0);
	}
	lst = cmd->args;
	name = ft_substr(lst->content, 0, ft_charfind(lst->content, '='));
	while (lst)
	{
		if (!valid_name(name, lst->content))
			return (free(name), 1);
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
	return (free(name), 0);
}
