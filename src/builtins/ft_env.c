/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:14 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/04 15:33:04 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_data *data)
{
	print_env(data, "%s=%s\n", NULL);
	return (0);
}

char	**envp_3_var(void)
{
	char	**array;

	array = (char **) malloc(4 * sizeof(char *));
	if (!array)
		return (NULL);
	array[0] = ft_strjoin("PWD=", (getcwd(NULL, 0)));
	array[1] = ft_strdup("SHLVL=1");
	array[2] = ft_strdup("_=/usr/bin/env");
	array[3] = NULL;
	return (array);
}

void	get_envp_3(t_data *data)
{
	int		i;
	char	*name;
	char	*value;
	char	**array;

	i = 0;
	name = NULL;
	value = NULL;
	array = envp_3_var();
	while (array[i])
	{
		name = ft_substr(array[i], 0, ft_charfind(array[i], '='));
		value = ft_substr(array[i], ft_charfind(array[i], '=') + 1,
				ft_strlen(array[i]));
		lst_add_back(&data->envp, lst_add_new(name, value));
		i++;
	}
}
