/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:31:55 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/01 08:35:52 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_out(t_io_node *io_list)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open(io_list->io_arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_in(t_io_node *io_list)
{
	int		fd;

	if (!io_list->io_arg)
		return (1);
	fd = open(io_list->io_arg, O_RDONLY);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_append(t_io_node *io_list)
{
	int	fd;

	if (!io_list->io_arg)
		return (1);
	fd = open(io_list->io_arg, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
