/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:28 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/22 19:03:10 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//envp in lst, separate value & name
void	get_envp(t_data *data, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	name = NULL;
	value = NULL;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_charfind(envp[i], '='));
        value = ft_substr(envp[i], ft_charfind(envp[i], '=') + 1,
			ft_strlen(envp[i]));
		lst_add_back(&data->envp, lst_add_new(name, value));
		i++;
	}
}

//envp in array, join name & value
char	**array_env(t_data *data, char *delimiter)
{
	char	**array;
	char	*join;
	int		i;

	if (!data->envp)
		return (NULL);
	array = ft_calloc(ft_llstsize(data->envp) + 1, sizeof(char *));
	i = 0;
	while (data->envp)
	{
		if (!delimiter)
			array[i++] = ft_strjoin(data->envp->name, data->envp->value);
		else
		{
			join = ft_strjoin(data->envp->name, delimiter);
			array[i++] = ft_strjoin(join, data->envp->value);
			free(join);
		}
		data->envp = data->envp->next;
	}
	array[i] = NULL;
	return (array);		
}

void	print_env(t_data *data, char *print1, char *print2)
{
	t_llist	*aux;
	char	*name;
	char	*value;

	if (!data->envp)
		return ;
	aux = data->envp;
	while (aux)
	{
		name = aux->name;
		value = aux->value;
		if (!value)
		{
			if (print2)
				printf(print2, (char *)name);
		}
		else if (!value[0])
			printf(print1, (char *)name, "");
		else
			printf(print1, (char *)name, (char *)value);
		aux = aux->next;
	}
}

char	*search_env(t_data *data, char *name)
{
	while (data->envp)
	{
		if (ft_strncmp((char *)data->envp->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(data->envp->name))
			return (data->envp->value);
		data->envp = data->envp->next;
	}
	return (NULL);
}

char	*check_envp(t_data *data, char *name, char *value)
{
	if (value)
		return (replace_env(data, name, value));
	return (search_env(data, name));
}
