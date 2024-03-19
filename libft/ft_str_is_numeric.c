/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:37:46 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/15 11:56:29 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_numeric(char *str)
{
	if (!(*str == '-' || *str == '+' || (*str >= '0' && *str <= '9')))
		return (0);
	if ((*str == '-' || *str == '+') && !(str[1] >= '0' && str[1] <= '9'))
		return (0);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (0);
	}
	return (1);
}
