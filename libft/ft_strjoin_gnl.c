/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:26:25 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/28 14:27:03 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_buff(char *add_read, char *str_buff)
{
	size_t	total_len;
	char	*str;
	size_t	i;
	size_t	j;

	total_len = ft_strlen(add_read) + ft_strlen(str_buff);
	str = (char *) malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	else
	{
		i = 0;
		j = 0;
		while (add_read && add_read[i] != '\0')
			str[j++] = add_read[i++];
		i = 0;
		while (str_buff[i] != '\0')
			str[j++] = str_buff[i++];
		str[j] = '\0';
	}
	free(add_read);
	return (str);
}
