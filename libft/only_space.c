/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:04:27 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/12 14:02:57 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	only_space(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			count++;
		i++;
	}
	if (count == ft_strlen(str))
		return (1);
	else
		return (0);
}
