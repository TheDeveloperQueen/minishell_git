/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:59:34 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/19 13:03:36 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *s1, char *s2, char c)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	new_str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	new_str[s1_len] = c;
	ft_strlcpy(new_str + s1_len + 1, s2, s2_len + 1);
	return (new_str);
}
