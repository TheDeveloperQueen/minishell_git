/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:17:41 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/04 11:30:11 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	*str;

	(void)cmd;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (0);
}
