/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:28 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/09 17:05:30 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_path(t_cmd *cmd)
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
		return (NULL);
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

void	print_cmd_not_found_error(char *cmd)
{
	char	*msg;

	if (cmd[0] == '\0')
		ft_putstr_fd("'': command not found\n", 2);
	else
	{
		msg = ft_strjoin(cmd, ": command not found\n");
		ft_putstr_fd(msg, 2);
		free(msg);
	}
}

char	*paths(t_data *data, t_cmd *cmd)
{
	char	**array_paths;
	char	*full_path;
	int		i;

	i = 0;
	if (has_path(cmd) == 0)
		return (ft_strdup(cmd->name));
	array_paths = find_path(data->envp);
	while (array_paths && array_paths[i] != NULL && cmd->name[0])
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
	print_cmd_not_found_error(cmd->name);
	clear_shell(data);
	exit(127);
}
