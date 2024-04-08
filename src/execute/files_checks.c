/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:15:58 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/08 08:39:51 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_error_msg(char *reason)
{
	char	*tmp1;
	char	*msg;

	tmp1 = ft_strjoin(SHELL_NAME, ": ");
	msg = ft_strjoin(tmp1, reason);
	free(tmp1);
	return (msg);
}

void	print_file_error(char *file)
{
	char	*msg;

	msg = create_error_msg(file);
	perror(msg);
	free(msg);
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
