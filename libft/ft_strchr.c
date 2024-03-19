/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:09:47 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/13 13:23:45 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*strlen;

	strlen = (char *)str;
	while (*strlen != (unsigned char)c)
	{
		if (!*strlen)
			return (NULL);
		strlen++;
	}
	return (strlen);
}
