/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:31:55 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/14 11:40:10 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int mode, int is_father)
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
		print_file_error(file);
		if (is_father == 0)
			exit(EXIT_FAILURE);
		else if (is_father == 1)
			return (-1);
	}
	return (fd);
}

int	ft_out(t_io_node *io_list, t_data *data, int is_father)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 1, is_father);
	if (fd < 0)
		return (1);
	do_dup2(fd, STDOUT_FILENO, data);
	close(fd);
	return (0);
}

int	ft_in(t_io_node *io_list, t_data *data, int is_father)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 0, is_father);
	if (fd < 0)
		return (1);
	do_dup2(fd, STDIN_FILENO, data);
	close(fd);
	return (0);
}

int	ft_append(t_io_node *io_list, t_data *data,
	int is_father)
{
	int	fd;

	if (!io_list->io_arg)
		return (1);
	fd = open_file(io_list->io_arg, 2, is_father);
	if (fd < 0)
		return (1);
	do_dup2(fd, STDOUT_FILENO, data);
	close(fd);
	return (0);
}
