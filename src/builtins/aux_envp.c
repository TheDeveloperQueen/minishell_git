/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:28 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/19 18:39:44 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//envp in lst, separate value & name
t_llist	*get_envp(char **envp)
{
	int		i;
    t_llist	*list;
	char	*name;
	char	*value;

	i = 0;
	list = NULL;
	name = NULL;
	value = NULL;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_charfind(envp[i], '='));
        value = ft_substr(envp[i], ft_charfind(envp[i], '=') + 1,
			ft_strlen(envp[i]));
		lst_add_back(&list, lst_add_new(name, value));
		i++;
	}
	return (list);
}

//envp in array, join name & value
char	**array_env(t_llist *lst, char *delimiter)
{
	char	**array;
	char	*join;
	int		i;

	if (!lst)
		return (NULL);
	array = ft_calloc(ft_llstsize(lst) + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		if (!delimiter)
			array[i++] = ft_strjoin(lst->name, lst->value);
		else
		{
			join = ft_strjoin(lst->name, delimiter);
			array[i++] = ft_strjoin(join, lst->value);
			free(join);
		}
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);		
}

void	print_env(t_llist *llst, char *print1, char *print2)
{
	t_llist	*aux;
	char	*name;
	char	*value;

	if (!llst)
		return ;
	aux = llst;
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

void	*search_env(t_llist *env, char *name)
{
	while (env)
	{
		if (ft_strncmp((char *)env->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*check_envp(t_data *data, char *name, char *value)
{
	if (value)
		return (replace_env(data->envp, name, value));
	return (search_env(data->envp, name));
}
