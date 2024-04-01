/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:58:05 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/01 08:17:39 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//commands args in list
void	get_args(t_command	*cmd)
{
	int		i;
	char	*str;

	i = 0;
	if (!cmd->args_splitted)
		return ;
	while (cmd->args_splitted[i])
	{
		str = ft_strdup(cmd->args_splitted[i]);
		//cmd->args_splitted[i] = NULL;
		ft_lstadd_back(&cmd->args, ft_lstnew(str));
		i++;
	}
}

//commands in array, name included
/*char	**get_array_cmds(t_command *cmd)
{
	char	**array;
	int		i;

	array = ft_calloc(ft_lstsize(cmd->args) + 2, sizeof(char *));
	if (!array)
		return (NULL);
	array[0] = ft_strdup(cmd->name);
	i = 0;
	while (cmd->args)
	{
		array[i++] = ft_strdup(cmd->args->content);
		cmd->args = cmd->args->next;
	}
	array[i] = NULL;
	return (array);	
}*/

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0 || ft_strcmp(cmd->name, "cd") == 0
		|| ft_strcmp(cmd->name, "pwd") == 0 || ft_strcmp(cmd->name, "export") == 0
		|| ft_strcmp(cmd->name, "unset") == 0 || ft_strcmp(cmd->name, "env") == 0
		|| ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	return (0);
}
