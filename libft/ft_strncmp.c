/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:52:12 by rivasque          #+#    #+#             */
/*   Updated: 2023/09/13 12:30:14 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t	i;

	i = 0;
	if (count == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (count - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
