/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:54:50 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/13 13:19:08 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char	*strdest;
	unsigned char	*strsrc;
	size_t			i;

	strdest = (unsigned char *)dest;
	strsrc = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (count--)
			strdest[count] = strsrc[count];
	else
	{
		while (i < count)
		{
			strdest[i] = strsrc[i];
			i++;
		}
	}
	return (dest);
}
