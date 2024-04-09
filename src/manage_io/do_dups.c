/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:56 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 12:03:50 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		perror("dup Error\n");
		exit(EXIT_FAILURE);
	}
	return (new_fd);
}

int	do_dup2(int fd1, int fd2, t_data *data)
{
	int	fd;

	fd = dup2(fd1, fd2);
	if (fd == -1)
	{
		perror("dup2 Error\n");
		clear_shell(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
