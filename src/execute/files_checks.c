/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:15:58 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/07 18:16:54 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_file_error(char *file)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(NULL);
}

int	check_path_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
		{
			print_file_error(path);
			return (126);
		}
		return (0);
	}
	print_file_error(path);
	return (127);
}
