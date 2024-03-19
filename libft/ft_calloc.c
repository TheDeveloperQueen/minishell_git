/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:57:36 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/12 11:05:04 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void			*str;
	size_t			i;
	unsigned char	*s;

	str = (void *) malloc(number * size);
	if (!str)
		return (NULL);
	i = 0;
	s = (unsigned char *)str;
	while (i < (number * size))
	{
		s[i] = (unsigned char)0;
		i++;
	}
	return ((void *)s);
}
