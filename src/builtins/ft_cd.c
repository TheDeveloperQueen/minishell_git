/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:42:27 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/21 11:59:46 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*path_home(t_command *cmd)
{
	char	*path;
	(void)cmd;

	path = getenv("HOME");
	if (chdir(path) < 0)
	{
		printf("HOME not set");
		return (NULL);
	}
	return (path);
}

static char	*find_path_old(t_command *cmd)
{
	char	*path;
	(void)cmd;

	path = getenv("OLDPWD");
	if (chdir(path) < 0)
	{
		printf("OLDPWD not set");
		return (NULL);
	}
	return (path);
}

static char	*find_path_args(t_command *cmd)
{
	char	*path;

	path = cmd->args->content;
	if (chdir(path) < 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (NULL);
	}
	return (path);
}

int	ft_cd(t_command *cmd)
{
	if (!cmd->args_splitted || ft_strcmp(cmd->args->content, "~") == 0)
		return (chdir(path_home(cmd)));
	else if (ft_strcmp(cmd->args->content, "-") == 0)
		return (chdir(find_path_old(cmd)));
	else
		return (chdir(find_path_args(cmd)));
	return (0);
}
