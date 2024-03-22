/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:08:32 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/22 20:08:27 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	get_fd_in(t_command *cmd)
 {
	char	*name;

	if (!cmd->infiles)
	{
		cmd->fd_in = -1;
		return ;
	}
	while (cmd->infiles)
	{
		cmd->fd_in = open_file(cmd->infiles->io_arg, 0);
		if (cmd->fd_in < 0)
        {
            ft_putstr_fd(cmd->infiles->io_arg, STDERR_FILENO);
            ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
		close_file(cmd->fd_in);
		if (cmd->infiles->next == NULL)
			break ;
        cmd->infiles = cmd->infiles->next;
    }
	if (cmd->infiles->io_type == IO_HEREDOC)
	{
		name = here_doc(cmd->infiles->io_arg);
		cmd->fd_in = open_file(name, 0);
	}
	else
		cmd->fd_in = open_file(cmd->infiles->io_arg, 0);
 }
 
 void	get_fd_out(t_command *cmd)
 {
	if (!cmd->outfiles)
	{
		cmd->fd_out = -1;
		return ;
	}
	while (cmd->outfiles)
	{
		cmd->fd_out = open_file(cmd->outfiles->io_arg, 1);
		if (cmd->fd_out < 0)
		{
            ft_putstr_fd(cmd->outfiles->io_arg, STDERR_FILENO);
            ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
		close_file(cmd->fd_out);
		if (cmd->outfiles->next == NULL)
			break ;
        cmd->outfiles = cmd->outfiles->next;
    }
	if (cmd->outfiles->io_type == IO_OUT)
		cmd->fd_out = open_file(cmd->outfiles->io_arg, 1);
	else if (cmd->outfiles->io_type == IO_APPEND)
		cmd->fd_out = open_file(cmd->outfiles->io_arg, 2);
 }
 