/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:15:58 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/08 07:10:02 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_file_error(char *file)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(SHELL_NAME, ": ");
	tmp2 = ft_strjoin(tmp1, file);
	perror(tmp2);
	free(tmp1);
	free(tmp2);
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
