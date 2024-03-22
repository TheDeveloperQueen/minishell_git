/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:17:41 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/22 15:31:38 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command *cmd)
{
	(void)cmd;
	char *str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (0);
}
