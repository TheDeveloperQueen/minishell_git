/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:04:46 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/14 09:35:24 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)buffer1;
	b2 = (unsigned char *)buffer2;
	i = 0;
	if (count == 0)
		return (0);
	while (b1[i] == b2[i] && i < count - 1)
		i++;
	return (b1[i] - b2[i]);
}
