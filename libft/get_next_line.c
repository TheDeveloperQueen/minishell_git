/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:55:17 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/28 14:32:23 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_cut(char *str)
{
	int		i;
	char	*str_print;

	if (!(str))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	str_print = (char *) malloc((i + 1) * sizeof(char));
	if (!str_print)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		str_print[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		str_print[i++] = '\n';
	str_print[i] = '\0';
	return (str_print);
}

char	*ft_str_left(char *str)
{
	int		i;
	int		j;
	char	*str_keep;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	str_keep = (char *) malloc((ft_strlen(str) - i) * sizeof(char));
	if (!str_keep)
		return (NULL);
	i += 1;
	while (str[i])
		str_keep[j++] = str[i++];
	free(str);
	str_keep[j] = '\0';
	return (str_keep);
}

char	*ft_print(char **add_read)
{
	char		*line;

	if (ft_strchr_int(*add_read, '\n'))
	{
		line = ft_str_cut(*add_read);
		*add_read = ft_str_left(*add_read);
		if (!(*add_read[0]))
		{
			free(*add_read);
			*add_read = NULL;
		}
		return (line);
	}
	line = ft_strdup(*add_read);
	free(*add_read);
	*add_read = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*add_read;
	char		*str_buff;
	int			bytesread;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
	{
		if (add_read)
			free(add_read);
		add_read = NULL;
		return (NULL);
	}
	str_buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str_buff)
		return (NULL);
	str_buff[0] = '\0';
	while (!ft_strchr_int(str_buff, '\n'))
	{
		bytesread = read(fd, str_buff, BUFFER_SIZE);
		str_buff[bytesread] = '\0';
		if (bytesread == 0)
			break ;
		add_read = ft_strjoin_buff(add_read, str_buff);
	}
	free(str_buff);
	return (ft_print(&add_read));
}
