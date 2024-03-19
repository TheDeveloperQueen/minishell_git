/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:50:29 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/19 15:16:47 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		op[3];
	int		count;
	char	**strs;

	op[0] = 0;
	op[1] = -1;
	count = ft_count_words(s, c);
	strs = (char **)malloc((count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++op[1] < count)
	{
		while (s[op[0]] == c)
			op[0]++;
		op[2] = ft_size_word(s, c, op[0]);
		strs[op[1]] = ft_substr(s, op[0], op[2]);
		if (!strs[op[1]])
		{
			ft_free(strs, op[1]);
			return (NULL);
		}
		op[0] += op[2];
	}
	strs[op[1]] = 0;
	return (strs);
}

/*/
* i = op[0]
* j = op[1]
size = op[2]
*/