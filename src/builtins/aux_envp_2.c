/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:08:03 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/10 10:54:31 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_envp_3(t_data *data)
{
	lst_add_back(&data->envp, lst_add_new(ft_strdup("PWD"), getcwd(NULL, 0)));
	lst_add_back(&data->envp, lst_add_new(ft_strdup("SHLVL"), ft_strdup("1")));
	lst_add_back(&data->envp, lst_add_new(ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
}

static void	set_mandatory_vars(t_data *data)
{
	if (!check_dup_env(data, "PWD"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("PWD"),
				getcwd(NULL, 0)));
	if (!check_dup_env(data, "SHLVL"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("SHLVL"),
				ft_strdup("1")));
	if (!check_dup_env(data, "_"))
		lst_add_back(&data->envp, lst_add_new(ft_strdup("_"),
				ft_strdup("/usr/bin/env")));
}

//envp in lst, separate value & name
static void	get_envp(t_data *data, char **envp)
{
	int		i;
	char	*name;
	char	*value;
	char	*tmp_value;
	int		tmp_value_i;

	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_charfind(envp[i], '='));
		if (ft_strcmp(name, "SHELL") == 0)
			value = ft_strdup(SHELL_NAME);
		else
			value = ft_substr(envp[i], ft_charfind(envp[i], '=') + 1,
					ft_strlen(envp[i]));
		if (ft_strcmp(name, "SHLVL") == 0)
		{
			tmp_value_i = ft_atoi(value);
			tmp_value = ft_itoa(tmp_value_i + 1);
			free(value);
			value = tmp_value;
		}
		lst_add_back(&data->envp, lst_add_new(name, value));
		i++;
	}
}

void	init_env(char **envp, t_data *data)
{
	if (envp == NULL || envp[0] == NULL)
		get_envp_3(data);
	else
	{
		get_envp(data, envp);
		set_mandatory_vars(data);
	}
}
