/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:58:05 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/18 19:51:31 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//commands args in list
t_list	*get_args(t_command	*cmd)
{
	int		i;
	t_list	*args;

	i = 2;
	args = NULL;
	while (cmd->args_splitted[i])
	{
		ft_lstadd_back(&args, ft_lstnew(cmd->args_splitted[i]));
		i++;
	}
	return (args);
}

//commands in array, name included
char	**get_array_cmds(t_command *cmd)
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
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0 || ft_strcmp(cmd->name, "cd") == 0
		|| ft_strcmp(cmd->name, "pwc") == 0 || ft_strcmp(cmd->name, "export") == 0
		|| ft_strcmp(cmd->name, "unset") == 0 || ft_strcmp(cmd->name, "env") == 0
		|| ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	return (0);
}
