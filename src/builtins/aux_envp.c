/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:28 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/04 10:57:54 by rivasque         ###   ########.fr       */
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
char	**array_env(t_llist *envp, char *delimiter)
{
	char	**array;
	char	*join;
	int		i;

	if (!envp)
		return (NULL);
	array = ft_calloc(ft_llstsize(envp) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (envp)
	{
		if (!delimiter)
			array[i++] = ft_strjoin(envp->name, envp->value);
		else
		{
			join = ft_strjoin(envp->name, delimiter);
			array[i++] = ft_strjoin(join, envp->value);
			free(join);
		}
		envp = envp->next;
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
	t_llist	*aux_env;

	aux_env = data->envp;
	while (aux_env)
	{
		if (ft_strncmp((char *)aux_env->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(aux_env->name))
			return (aux_env->value);
		aux_env = aux_env->next;
	}
	return (NULL);
}

char	*check_envp(t_data *data, char *name, char *value)
{
	if (value)
		replace_env(data, name, value);
	return (search_env(data, name));
}
