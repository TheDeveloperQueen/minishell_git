/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:26:57 by ritavasques       #+#    #+#             */
/*   Updated: 2023/10/12 12:24:32 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_line_length(int fd)
{
	char	line[1];
	int		bytesread;
	int		length;

	line[0] = '\0';
	bytesread = 1;
	length = 0;
	while (bytesread == 1)
	{
		bytesread = read(fd, line, 1);
		if (line[0] != '\n')
			length++;
		else
			break ;
	}
	return (length);
}
