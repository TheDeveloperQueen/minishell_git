/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:10:51 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/13 10:26:18 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*strdest;

	strdest = (unsigned char *)dest;
	i = 0;
	while (i < count)
	{
		strdest[i] = c;
		i++;
	}
	return (dest);
}
