/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:13:15 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 11:52:53 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_char_and_free(char *old_str, char c)
{
	char	*new_str;
	char	*char_to_str;

	char_to_str = malloc(sizeof(char) * 2);
	if (!char_to_str)
		return (free(old_str), NULL);
	char_to_str[0] = c;
	char_to_str[1] = '\0';
	new_str = ft_strjoin(old_str, char_to_str);
	if (!new_str)
	{
		free(old_str);
		free(char_to_str);
		return (NULL);
	}
	free(char_to_str);
	free(old_str);
	return (new_str);
}

char	*get_var_name(char **str)
{
	int		i;
	char	*var_name;

	if (*str[0] == '$')
		(*str)++;
	if (ft_isdigit(*str[0]))
	{
		var_name = ft_substr(*str, 0, 1);
		if (!var_name)
			return (NULL);
		(*str)++;
		return (var_name);
	}
	i = 0;
	while ((*str)[i] && !ft_is_quote((*str)[i]) && !ft_is_space((*str)[i])
			&& (*str)[i] != '$')
		i++;
	var_name = ft_substr(*str, 0, i);
	if (!var_name)
		return (NULL);
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

char	*add_var_and_free(char *old_str, char *var_name, t_llist *envp)
{
	char	*new_str;
	char	*var;

	var = my_get_env(var_name, envp);
	if (!var)
		return (old_str);
	new_str = ft_strjoin(old_str, var);
	if (!new_str)
		return (free(old_str), NULL);
	free(old_str);
	return (new_str);
}

char	*expand_env_vars(char *word, t_llist *envp)
{
	char	*new_word;
	int		start_quote;
	char	*var_name;

	new_word = ft_get_empty_str();
	start_quote = 0;
	while (new_word && *word)
	{
		if (*word == '\'' && !start_quote)
			start_quote = 1;
		else if (*word == '\'' && start_quote)
			start_quote = 0;
		if (*word == '$' && !start_quote && *(word + 1))
		{
			var_name = get_var_name(&word);
			if (!var_name)
				return (free(new_word), NULL);
			new_word = add_var_and_free(new_word, var_name, envp);
			free(var_name);
		}
		else
			new_word = add_char_and_free(new_word, *word++);
	}
	return (new_word);
}
