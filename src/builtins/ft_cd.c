/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:42:27 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 13:16:24 by acoto-gu         ###   ########.fr       */
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

static int	path_home(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*old;

	(void)cmd;
	old = getcwd(NULL, 0);
	path = search_env(data, "HOME");
	if (!path)
	{
		printf("%s: HOME not set", SHELL_NAME);
		return (1);
	}
	if (opendir(path))
		chdir(path);
	else
		return (1);
	manage_path(data, old);
	return (0);
}

static int	path_old(t_data *data, t_cmd *cmd)
{
	char	*old;
	char	*path;

	(void)cmd;
	old = getcwd(NULL, 0);
	path = search_env(data, "OLDPWD");
	if (!path)
	{
		printf("%s: OLDPWD not set", SHELL_NAME);
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

int	check_args_size(t_cmd *cmd, int limit_size)
{
	int		args_size;
	char	*tmp_msg_1;
	char	*tmp_msg_2;
	char	*msg;

	args_size = ft_lstsize(cmd->args);
	if (args_size > limit_size)
	{
		tmp_msg_1 = create_error_msg(cmd->name);
		tmp_msg_2 = ft_strjoin(tmp_msg_1, ": ");
		msg = ft_strjoin(tmp_msg_2, "too many arguments\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		return (free(tmp_msg_1), free(tmp_msg_2), free(msg), 1);
	}
	return (0);
}

int	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*old;

	if (check_args_size(cmd, 1))
		return (1);
	old = getcwd(NULL, 0);
	if (!cmd->args || ft_strcmp(cmd->args->content, "~") == 0)
		return (path_home(data, cmd));
	else if (ft_strcmp(cmd->args->content, "-") == 0)
		return (path_old(data, cmd));
	else if (opendir((char *)cmd->args->content))
		chdir((char *)cmd->args->content);
	else
	{
		printf("%s: cd: %s: No such file or directory\n", SHELL_NAME,
			(char *)cmd->args->content);
		return (1);
	}
	manage_path(data, old);
	return (0);
}
