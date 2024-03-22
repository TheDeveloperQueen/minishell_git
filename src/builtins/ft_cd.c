/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:42:27 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 19:04:30 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_path(t_data *data, char *old)
{
	if (!check_dup_env(data, "OLDPWD"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("OLDPWD"), NULL));
	check_envp(data, "OLDPWD", old);
	if (!check_dup_env(data, "PWD"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("PWD"), NULL));
	check_envp(data, "PWD", getcwd(NULL, 0));
	return (0);
}

static int	path_home(t_data *data, t_command *cmd)
{
	char	*path;
	char	*old;
	(void)cmd;

	old = getcwd(NULL, 0);
	path = search_env(data, "HOME");
	if (!path)
	{
		printf("ourShell: HOME not set");
		return (1);
	}
	if (opendir(path))
		chdir(path);
	else
		return (1);
	manage_path(data, old);
	return (0);
}

static int	path_old(t_data *data, t_command *cmd)
{
	char	*old;
	char	*path;
	(void)cmd;

	old = getcwd(NULL, 0);
	path = search_env(data, "OLDPWD");
	if (!path)
	{
		printf("ourShell: OLDPWD not set");
		if (!check_dup_env(data, "OLDPWD"))
			lst_add_back(&data->envp, lst_add_new(ft_strdup("OLDPWD"), NULL));
		return (1);
	}
	if (opendir(path))
	{
		chdir(path);
		printf("%s\n", path);
	}
	manage_path(data, old);
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd)
{
	char	*old;
	
	old = getcwd(NULL, 0);
	if (!cmd->args || ft_strcmp(cmd->args->content, "~") == 0)
		return (path_home(data, cmd));
	else if (ft_strcmp(cmd->args->content, "-") == 0)
		return (path_old(data, cmd));
	else if (opendir((char *)cmd->args->content))
		chdir((char *)cmd->args->content);
	else
	{
		printf("cd: %s: No such file or directory\n", (char *)cmd->args->content);
		return (1);
	}
	manage_path(data, old);
	return (0);
}
