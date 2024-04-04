/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:05:49 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 23:09:20 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_quote_state(char c, int *quote_state)
{
	if (c == '\"' && *quote_state == 0)
		*quote_state = 1;
	else if (c == '\"' && *quote_state == 1)
		*quote_state = 0;
	else if (c == '\'' && *quote_state == 0)
		*quote_state = 2;
	else if (c == '\'' && *quote_state == 2)
		*quote_state = 0;
}

static int	count_words(char const *s, char c)
{
	int	word_count;
	int	i;
	int	quote_state;

	i = 0;
	quote_state = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (s[i - 1] == c && quote_state == 0)))
		{
			word_count++;
		}
		set_quote_state(s[i], &quote_state);
		i++;
	}
	return (word_count);
}

static char	**free_arr(char **str_arr, int n_words)
{
	int	i;

	i = 0;
	while (i < n_words)
		free (str_arr[i++]);
	free(str_arr);
	return (0);
}

static char	**split(char **str_arr, char const *s, char c, int n_words)
{
	int	i;
	int	num_words;
	int	w_len;
	int quote_state;

	i = 0;
	num_words = 0;
	w_len = 0;
	while (num_words < n_words)
	{
		quote_state = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && (s[i] != c || quote_state > 0))
		{
			set_quote_state(s[i], &quote_state);
			i++;
			w_len++;
		}
		str_arr[num_words] = ft_substr(s, i - w_len, w_len);
		if (!str_arr[num_words])
			return (free_arr(str_arr, num_words));
		w_len = 0;
		num_words++;
	}
	str_arr[num_words] = NULL;
	return (str_arr);
}

char	**special_split(char const *s, char c)
{
	char	**ptr;
	int		n_words;

	if (!s)
		return (NULL);
	n_words = count_words(s, c);
	ptr = malloc(sizeof(char *) * (n_words + 1));
	if (!ptr)
		return (NULL);
	ptr = split(ptr, s, c, n_words);
	return (ptr);
}
