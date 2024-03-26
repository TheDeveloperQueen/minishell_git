/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:28 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/26 14:43:11 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_path(t_command *cmd)
{
	int	flag;

	flag = 1;
	if (cmd->name)
	{
		if (ft_strchr(cmd->name, '/'))
			flag = 0;
	}
	return (flag);
}

static char	**find_path(t_llist *envp)
{
	char	**paths;

	if (!envp)
		perror("error");
	while (envp)
	{
		if (ft_strcmp(envp->name, "PATH") == 0)
			break ;
		envp = envp->next;
	}
	if (envp == NULL)
		return (NULL);
	paths = ft_split(envp->value, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*paths(t_data *data, t_command *cmd)
{
	char	**array_paths;
	char	*full_path;
	int		i;

	i = 0;
	if (has_path(cmd) == 0)
		return (cmd->name);
	array_paths = find_path(data->envp);
	while (array_paths && array_paths[i] != NULL)
	{
		full_path = ft_strjoin(array_paths[i], "/");
		full_path = ft_strjoin(full_path, cmd->name);
		if (access(full_path, F_OK) == 0)
		{
			free(array_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd(cmd->name, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}
