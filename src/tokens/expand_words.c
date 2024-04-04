/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:13:15 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 23:18:35 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_start_name(char c)
{
	if (!ft_isalpha(c) && c != '_')
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
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
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

void	add_var_and_free(char **old_str, char *var_name, t_llist *envp)
{
	char	*new_str;
	char	*var;

	var = my_get_env(var_name, envp);
	free (var_name);
	if (!var)
	{
		free(*old_str);
		old_str = NULL;
		return ;
	}
	new_str = ft_strjoin(*old_str, var);
	free(*old_str);
	if (!new_str)
		*old_str = NULL;
	else
		*old_str = new_str;
}

void	set_start_quote(char c, int *start_quote)
{
	if (c == '\"' && *start_quote == 0)
		*start_quote = 1;
	else if (c == '\"' && *start_quote == 1)
		*start_quote = 0;
	else if (c == '\'' && *start_quote == 0)
		*start_quote = 2;
	else if (c == '\'' && *start_quote == 2)
		*start_quote = 0;
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
		set_start_quote(*word, &start_quote);
		if (*word == '\\' && (start_quote < 2) && *(++word))
			add_char_and_free(&new_word, *(word++));
		else if (*word == '$' && (start_quote < 2) && (*(word + 1))
			&& (start_quote == 0 || is_valid_start_name(*(word + 1))))
		{
			var_name = get_var_name(&word);
			if (!var_name)
				return (free(new_word), NULL);
			add_var_and_free(&new_word, var_name, envp);
		}
		else if (*word)
			add_char_and_free(&new_word, *word++);
	}
	return (new_word);
}
