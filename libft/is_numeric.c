/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:37:46 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/14 11:12:56 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_numeric(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-' && str[0] == '-' && str[1] != '\0')
			count++;
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}
