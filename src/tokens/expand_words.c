/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:13:15 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/12 15:18:21 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_start_name(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

void	add_char_and_free(char **old_str, char c)
{
	char	*new_str;
	char	*char_to_str;

	char_to_str = malloc(sizeof(char) * 2);
	if (!char_to_str)
	{
		free(*old_str);
		*old_str = NULL;
		return ;
	}
	char_to_str[0] = c;
	char_to_str[1] = '\0';
	new_str = ft_strjoin(*old_str, char_to_str);
	free(char_to_str);
	free(*old_str);
	if (!new_str)
		*old_str = NULL;
	else
		*old_str = new_str;
}

char	*get_var_name(char **str, int is_between_quotes)
{
	int		i;
	char	*var_name;

	if ((*str)[0] == '$')
		(*str)++;
	if ((*str)[0] == '?')
	{
		*str = *str + 1;
		var_name = ft_strdup("?");
		return (var_name);
	}
	if (((*str)[0] == '\"' || (*str)[0] == '\'') && !is_between_quotes)
		return (ft_strdup(""));
	if ((*str)[0] == 0 || !is_valid_start_name((*str)[0]))
		return (ft_strdup("$"));
	i = 0;
	while ((*str)[i] && (is_valid_start_name((*str)[i])))
		i++;
	var_name = ft_substr(*str, 0, i);
	*str = *str + i;
	return (var_name);
}

char	*my_get_env(char *var_name, t_llist *envp)
{
	while (envp)
	{
		if (ft_strcmp(var_name, envp->name) == 0
			&& ft_strlen(var_name) == ft_strlen(envp->name))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	add_var_and_free(char **old_str, char *var_name, t_data *data)
{
	char	*new_str;
	char	*var;

	if (ft_strcmp(var_name, "?") == 0)
		var = ft_itoa(data->status);
	else if (ft_strcmp(var_name, "$") == 0)
		var = ft_strdup("$");
	else
		var = my_get_env(var_name, data->envp);
	if (!var)
	{
		free (var_name);
		return ;
	}
	new_str = ft_strjoin(*old_str, var);
	if ((ft_strcmp(var_name, "?") == 0) || (ft_strcmp(var_name, "$") == 0))
		free(var);
	free(var_name);
	free(*old_str);
	if (!new_str)
		*old_str = NULL;
	else
		*old_str = new_str;
}
