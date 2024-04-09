/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:04:10 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/09 15:13:25 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_msg(char *reason, char *msg)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(SHELL_NAME, ": ");
	str2 = ft_strjoin(str1, reason);
	free(str1);
	str1 = ft_strjoin(str2, ": ");
	free(str2);
	str2 = ft_strjoin(str1, msg);
	ft_putendl_fd(str2, STDERR_FILENO);
	free(str1);
	free(str2);
}
