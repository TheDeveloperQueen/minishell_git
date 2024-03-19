/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:13:24 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/07 17:20:00 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charfind(char *str, char c)
{
	int	i;

    i = 0;
	if (!str || !c)
		return (0);
	while (str[i] != c) 
			i++;
    return (i);
}
