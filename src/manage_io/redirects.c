/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:31:55 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/03 15:55:05 by rivasque         ###   ########.fr       */
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

int	ft_out(t_io_node *io_list, t_data *data, t_commands_array *cmds)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 1);
	if (fd < 0)
	{
        ft_putstr_fd(io_list->io_arg, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
	do_dup2(fd, STDOUT_FILENO, data, cmds);
	close(fd);
	return (0);
}

int	ft_in(t_io_node *io_list, t_data *data, t_commands_array *cmds)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 0);
	if (fd < 0)
	{
        ft_putstr_fd(io_list->io_arg, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
	do_dup2(fd, STDIN_FILENO, data, cmds);
	close(fd);
	return (0);
}

int	ft_append(t_io_node *io_list, t_data *data, t_commands_array *cmds)
{
	int	fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 2);
	if (fd < 0)
	{
        ft_putstr_fd(io_list->io_arg, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
	do_dup2(fd, STDOUT_FILENO, data, cmds);
	close(fd);
	return (0);
}
