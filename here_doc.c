/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:19:31 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/18 18:56:31 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_here_doc(int fd, char *delimiter)
{
	char	*line;

	//signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	//signals();
}

char	*here_doc(char *delimiter)
{
	int		fd;
	char	*path;
	int		file_ok;

	if (!delimiter)
		return (NULL);
	path = ft_calloc(10, sizeof(char));
	if (!path)
		return (NULL);
	ft_strcpy(path, "./heredoc");
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(path);
		return (NULL);
	}
	file_ok = read_here_doc(fd, delimiter);
	close(fd);
	if (!file_ok)
		return (NULL);
	return (path);
}

int has_here_doc(t_command *cmd, t_data *data)
{
    while (cmd->infiles)
        cmd->infiles = cmd->infiles->next;
    if (cmd->infiles->io_type == IO_HEREDOC)
        data->heredoc = 1;
    else
        data->heredoc = 0;
    return (0);
}
