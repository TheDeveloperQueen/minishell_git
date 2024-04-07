/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:13:15 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/07 13:41:29 by acoto-gu         ###   ########.fr       */
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
	free (var_name);
	if (!var)
		return ;
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

char	*expand_env_vars(char *word, t_data *data)
{
	char	*new_word;
	int		start_quote;
	char	*var_name;

	new_word = ft_get_empty_str();
	start_quote = 0;
	while (new_word && *word)
	{
		set_start_quote(*word, &start_quote);
		if (*word == '$' && (start_quote < 2))
		{
			var_name = get_var_name(&word, start_quote);
			if (!var_name)
				return (free(new_word), NULL);
			add_var_and_free(&new_word, var_name, data);
		}
		else if (*word == '\\' && (start_quote < 2) && *(++word))
			add_char_and_free(&new_word, *(word++));
		else if (*word)
			add_char_and_free(&new_word, *word++);
	}
	return (new_word);
}

char	*take_out_quotes(char *str)
{
	char	quote_char;
	int		start_quote;
	char	*new_str;

	start_quote = 0;
	new_str = ft_get_empty_str();
	while (new_str && *str)
	{
		if (ft_is_quote(*str) && !start_quote)
		{
			start_quote = 1;
			quote_char = *str;
		}
		else if (ft_is_quote(*str) && start_quote && *str == quote_char)
			start_quote = 0;
		else
			add_char_and_free(&new_str, *str);
		str++;
	}
	return (new_str);
}

int	expand_tokens(t_token_node *tkn_lst, t_data *data)
{
	char	*temp1;
	char	*temp2;
	char	*str;

	while (tkn_lst)
	{
		if (tkn_lst->type == T_WORD && tkn_lst->io_type != IO_HEREDOC)
		{
			str = tkn_lst->content;
			temp1 = expand_env_vars(str, data);
			if (!temp1)
				return (1);
			temp2 = take_out_quotes(temp1);
			if (!temp2)
				return (free(temp1), 1);
			free(temp1);
			free (str);
			tkn_lst->content = temp2;
		}
		tkn_lst = tkn_lst->next;
	}
	return (0);
}
