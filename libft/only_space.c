/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:04:27 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/11 12:21:59 by rivasque         ###   ########.fr       */
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
		if (str[i] == ' ')
			count++;
		i++;
	}
	if (count == ft_strlen(str))
		return (1);
	else
		return (0);
}
