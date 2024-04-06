/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:52:20 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/05 22:26:58 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_expand_str_arr(char	**str_arr, t_data *data)
{
	int		i;
	char	*temp1;
	char	*temp2;
	char	*str;

	i = 0;
	while (str_arr[i])
	{
		str = str_arr[i];
		temp1 = expand_env_vars(str, data);
		if (!temp1)
			return (1);
		temp2 = take_out_quotes(temp1);
		if (!temp2)
			return (free(temp1), 1);
		free(temp1);
		free (str);
		str_arr[i] = temp2;
		i++;
	}
	return (0);
}
