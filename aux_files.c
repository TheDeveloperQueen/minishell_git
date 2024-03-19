/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:08:32 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/19 10:52:31 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	if (mode == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mode == 2)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	get_fd_in(t_command *cmd, t_io_node *fd)
 {
	char	*name;
	
	while (cmd->infiles)
	{
		cmd->fd_in = open_file(fd->io_arg, 0);
		if (cmd->fd_in < 0)
        {
            ft_putstr_fd(fd->io_arg, STDERR_FILENO);
            ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
		close_file(cmd->fd_in);
        cmd->infiles = cmd->infiles->next;
    }
	if (fd->io_type == IO_HEREDOC)
	{
		name = here_doc(fd->io_arg);
		cmd->fd_in = open_file(name, 0);
	}
	else
		cmd->fd_in = open_file(fd->io_arg, 0);
	return (cmd->fd_in);
 }
 
 int	get_fd_out(t_command *cmd, t_io_node *file, t_data *data)
 {
	while (cmd->outfiles)
	{
		cmd->fd_out = open_file(file->io_arg, 1);
		if (cmd->fd_out < 0)
		{
            ft_putstr_fd(file->io_arg, STDERR_FILENO);
            ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
		close_file(cmd->fd_out);
        cmd->infiles = cmd->infiles->next;
    }
	if (file->io_type == IO_OUT && data->heredoc == 0)
		cmd->fd_out = open_file(file->io_arg, 1);
	else if (file->io_type == IO_APPEND || data->heredoc == 1)
		cmd->fd_out = open_file(file->io_arg, 2);
	return (cmd->fd_out);
 }
 