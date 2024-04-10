/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:28 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/10 11:00:41 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//envp in array, join name & value
char	**array_env(t_llist *envp)
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
		if (envp->value)
		{
			join = ft_strjoin(envp->name, "=");
			array[i++] = ft_strjoin(join, envp->value);
			free(join);
		}
		else
			array[i++] = ft_strdup(envp->name);
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
