/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:50:29 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/25 12:03:34 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// static int	ft_count_words(char const *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 	}
// 	return (count);
// }

// static int	ft_size_word(char const *s, char c, int i)
// {
// 	int	size;

// 	size = 0;
// 	while (s[i] != c && s[i])
// 	{
// 		size++;
// 		i++;
// 	}
// 	return (size);
// }

// static void	ft_free(char **strs, int j)
// {
// 	while (j-- > 0)
// 		free(strs[j]);
// 	free(strs);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		op[3];
// 	int		count;
// 	char	**strs;

// 	op[0] = 0;
// 	op[1] = -1;
// 	count = ft_count_words(s, c);
// 	strs = (char **)malloc((count + 1) * sizeof(char *));
// 	if (!strs)
// 		return (NULL);
// 	while (++op[1] < count)
// 	{
// 		while (s[op[0]] == c)
// 			op[0]++;
// 		op[2] = ft_size_word(s, c, op[0]);
// 		strs[op[1]] = ft_substr(s, op[0], op[2]);
// 		if (!strs[op[1]])
// 		{
// 			ft_free(strs, op[1]);
// 			return (NULL);
// 		}
// 		op[0] += op[2];
// 	}
// 	strs[op[1]] = 0;
// 	return (strs);
// }

/*/
* i = op[0]
* j = op[1]
size = op[2]
*/

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
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

	i = 0;
	num_words = 0;
	w_len = 0;
	while (num_words < n_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
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

char	**ft_split(char const *s, char c)
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