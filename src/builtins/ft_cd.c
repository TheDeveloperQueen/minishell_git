/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:42:27 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/11 16:03:35 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_path(t_data *data, char *old)
{
	char	*new_pwd;
	
	new_pwd = getcwd(NULL, 0);
	if (!check_dup_env(data, "OLDPWD"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("OLDPWD"), old));
	else
		check_envp(data, "OLDPWD", old);
	if (!check_dup_env(data, "PWD"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("PWD"), new_pwd));
	else
		check_envp(data, "PWD", new_pwd);
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
		printf("%s: HOME not set\n", SHELL_NAME);
		return (1);
	}
	if (opendir(path))
		chdir(path);
	else
		return (1);
	manage_path(data, old);
	return (free(path), 0);
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
		printf("%s: OLDPWD not set\n", SHELL_NAME);
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
	char	*msg;
	char	*msg2;

	if (check_args_size(cmd, 1))
		return (1);
	if (!cmd->args || ft_strcmp(cmd->args->content, "~") == 0)
		return (path_home(data, cmd));
	else if (ft_strcmp(cmd->args->content, "-") == 0)
		return (path_old(data, cmd));
	else if (opendir((char *)cmd->args->content))
	{
		old = getcwd(NULL, 0);
		chdir((char *)cmd->args->content);
		manage_path(data, old);
	}
	else
	{
		msg = ft_strjoin(cmd->name, ": ");
		msg2 = ft_strjoin(msg, cmd->args->content);
		print_error_msg(msg2, "No such file or directory");
		return (free(msg), free(msg2), 1);
	}
	return (0);
}
