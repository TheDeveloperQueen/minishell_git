/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:27:31 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/28 12:53:39 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;
	size_t	j;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc ((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	else
	{
		i = 0;
		j = 0;
		while (s1[i] != '\0')
			str[j++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			str[j++] = s2[i++];
		str[j] = '\0';
	}
	return (str);
}
