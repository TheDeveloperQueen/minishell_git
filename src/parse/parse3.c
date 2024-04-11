/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:24:33 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/11 12:28:08 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_str_arr(t_list *cmd_name_and_args)
{
	char	**str_arr;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(cmd_name_and_args);
	str_arr = malloc(sizeof(char *) * (lst_size + 1));
	if (!str_arr)
		return (NULL);
	i = 0;
	while (cmd_name_and_args)
	{
		str_arr[i] = cmd_name_and_args->content;
		i++;
		cmd_name_and_args = cmd_name_and_args->next;
	}
	str_arr[lst_size] = NULL;
	return (str_arr);
}

int	set_name_and_args_fields(t_cmd_array *cmds)
{
	char		**str_arr;
	int			i;
	t_cmd		*cmd;

	i = 0;
	while (i < cmds->len)
	{
		cmd = cmds->array[i];
		if (cmd->name_and_args)
		{
			if (cmd->name_and_args->next)
				cmd->args = cmd->name_and_args->next;
			str_arr = create_str_arr(cmd->name_and_args);
			if (!str_arr)
				return (1);
			cmd->name_and_args_splt = str_arr;
			if (str_arr[0])
				cmd->name = str_arr[0];
		}
		i++;
	}
	return (0);
}
